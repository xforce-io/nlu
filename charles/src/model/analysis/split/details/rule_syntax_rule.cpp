#include "../rule_syntax_rule.h"

namespace xforce { namespace nlu { namespace charles {

const std::wstring RuleSyntaxRule::kBranch0SyntaxStoragePrefix = L"/branch0-syntactic";
const std::wstring RuleSyntaxRule::kBranch1SyntaxStoragePrefix = L"/branch1-syntactic";
const std::wstring RuleSyntaxRule::kBranch2SyntaxStoragePrefix = L"/branch2-syntactic";

RuleSyntaxRule::RuleSyntaxRule(
        std::shared_ptr<milkie::FeatureExtractor> &featureExtractor) :
  featureExtractor_(featureExtractor) {}

bool RuleSyntaxRule::Split(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  std::vector<std::shared_ptr<basic::NluContext>> branches;
  branches.resize(kMaxNumBranches, nullptr);

  auto context = std::make_shared<milkie::Context>(nluContext);
  auto errCode = featureExtractor_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return false;
  }

  const milkie::Storage &storage = context->GetStorage();
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
      branches[index] = nluContext->Clone();
    }

    auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
    if (basic::SyntaxTag::Type::kUndef == syntaxTag) {
      ERROR("unknown_syntax_tag[" << syntaxTag << "]");
      return false;
    }

    auto storageItems = storageKv.second->Get();
    for (auto &storageItem : storageItems) {
      basic::Chunk chunk(
              syntaxTag,
              storageItem.GetOffset(),
              storageItem.GetContent().length());
      if (branches[index]->GetChunks().Add(chunk)) {
        if (basic::SyntaxTag::Type::kStc == syntaxTag) {
          return true;
        }
      }
    }
  }

  bool touched = false;
  for (size_t i=0; i<kMaxNumBranches; ++i) {
    if (nullptr != branches[i]) {
      nluContexts.push_back(branches[i]);
      touched = true;
    }
  }
  return touched;
}

}}}