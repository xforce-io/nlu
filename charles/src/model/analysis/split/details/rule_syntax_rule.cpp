#include "../rule_syntax_rule.h"
#include "../split_stage.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

const std::wstring RuleSyntaxRule::kBranch0SyntaxStoragePrefix = L"/branch0_syntactic";
const std::wstring RuleSyntaxRule::kBranch1SyntaxStoragePrefix = L"/branch1_syntactic";
const std::wstring RuleSyntaxRule::kBranch2SyntaxStoragePrefix = L"/branch2_syntactic";

RuleSyntaxRule::RuleSyntaxRule(
        std::shared_ptr<milkie::FeatureExtractor> &featureExtractor) :
  featureExtractor_(featureExtractor),
  context_(nullptr) {}

bool RuleSyntaxRule::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  std::vector<std::shared_ptr<basic::NluContext>> branches;
  branches.resize(kMaxNumBranches, nullptr);

  context_ = std::make_shared<milkie::Context>(nluContext);
  auto errCode = featureExtractor_->MatchPattern(*context_);
  if (milkie::Errno::kOk != errCode) {
    context_ = nullptr;
    return false;
  }

  const milkie::Storage &storage = context_->GetStorage();
  bool touched = false;
  for (auto &storageKv : storage.Get()) {
    const milkie::StorageKey &key = storageKv.first;
    std::wstring repr;
    key.GetRepr(repr);

    std::vector<std::wstring> vals;
    StrHelper::SplitStr(repr, L'.', vals);
    if (vals.size() != 2) {
      continue;
    }

    int index = -1;
    if (kBranch0SyntaxStoragePrefix == vals[0]) {
      index = 0;
    } else if (kBranch1SyntaxStoragePrefix == vals[0]) {
      index = 1;
    } else if (kBranch2SyntaxStoragePrefix == vals[0]) {
      index = 2;
    }

    if (index<0){
      FATAL("invalid_branch_syntax_parse_prefix[" << vals[0] << "]");
      continue;
    }

    if (nullptr == branches[index]) {
      branches[index] = Rule::Clone(splitStage, nluContext);
    }

    auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
    if (basic::SyntaxTag::Type::kUndef == syntaxTag) {
      context_ = nullptr;
      ERROR("unknown_syntax_tag[" << syntaxTag << "]");
      return false;
    }

    bool curTouched = false;
    auto storageItems = storageKv.second->Get();
    for (auto &storageItem : storageItems) {
      basic::Chunk chunk(
              *nluContext,
              syntaxTag,
              storageItem.GetOffset(),
              storageItem.GetContent().length(),
              930);
      if (branches[index]->GetChunks().Add(chunk)) {
        curTouched = true;
      }
    }

    if (curTouched) {
      touched = true;
    } else {
      branches[index] = nullptr;
    }
  }

  for (size_t i=0; i<kMaxNumBranches; ++i) {
    if (nullptr != branches[i]) {
      nluContexts.push_back(branches[i]);
    }
  }

  if (!touched) {
    context_ = nullptr;
  }
  return touched;
}

bool RuleSyntaxRule::GenForbid(ForbidItem &forbidItem) const {
  if (context_ == nullptr) {
    return false;
  }

  forbidItem.SetCategoryRule(Rule::kCategoryRuleSyntaxRule);
  forbidItem.SetOffset(context_->GetStartPos());
  forbidItem.SetLen(context_->GetCurPos() - context_->GetStartPos());
  return true;
}

bool RuleSyntaxRule::PostCheckForbid(const ForbidItem &forbidItem) const {
  return forbidItem.GetCategoryRule() == Rule::kCategoryRuleSyntaxRule &&
      nullptr != context_ &&
      context_->GetStartPos() == forbidItem.GetOffset() &&
      context_->GetCurPos() - context_->GetStartPos() == forbidItem.GetLen();
}

Rule* RuleSyntaxRule::Clone() {
  return new RuleSyntaxRule(featureExtractor_);
}

}}}
