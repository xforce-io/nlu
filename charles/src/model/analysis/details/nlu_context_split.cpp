#include "../nlu_context_split.h"
#include "../../../conf/conf.h"

namespace xforce { namespace nlu { namespace charles {

const std::wstring NluContextSplit::kBranch0SyntaxStoragePrefix = L"/branch0_syntactic";
const std::wstring NluContextSplit::kBranch1SyntaxStoragePrefix = L"/branch1_syntactic";
const std::wstring NluContextSplit::kBranch2SyntaxStoragePrefix = L"/branch2_syntactic";

NluContextSplit::NluContextSplit() :
  splitRuleEngine_(nullptr) {}

NluContextSplit::~NluContextSplit() {
  XFC_DELETE(splitRuleEngine_)
}

bool NluContextSplit::Init() {
  splitRuleEngine_ = new milkie::Milkie();

  bool ret = splitRuleEngine_->Init(Conf::Get().GetSplitRuleConfpath());
  if (!ret) {
    FATAL("fail_init[split_rule_engine] confpath[" 
        << *StrHelper::Str2Wstr(Conf::Get().GetSplitRuleConfpath()) 
        << "]");
    return false;
  }

  feNluContextSplit_ = splitRuleEngine_->GetManager().GetFeatureExtractor(L"nluContextSplit");
  if (nullptr == feNluContextSplit_) {
    FATAL("fail_get_feature_extractor_named_nlu_context_split");
    return false;
  }
  return true;
}

void NluContextSplit::Split(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
        basic::Stage::Val stage) {
  switch (stage) {
    case basic::Stage::Val::kPosTag : {
      SplitByPosTag_(nluContext, nluContexts);
    }
    case basic::Stage::Val::kSyntax : {
      SplitBySyntax_(nluContext, nluContexts);
    }
    default : {
      break;
    }
  }
}

void NluContextSplit::SplitByPosTag_(
        const std::shared_ptr<basic::NluContext> &nluContext,
        CollectionNluContext &nluContexts) {
  auto iterSeg = nluContext->GetSegments().GetAll().begin();
  size_t idx=0;
  while (iterSeg != nluContext->GetSegments().GetAll().end()) {
    if ((*iterSeg)->GetTags().size() > 1) {
      for (auto tag : ((*iterSeg)->GetTags())) {
        auto newNluContext = nluContext->Clone();
        AdjustSegTags_(*newNluContext, idx, tag);
        nluContexts.Add(newNluContext);
      }

      if (nluContexts.NonEmpty()) {
        return;
      }
    }
    ++iterSeg;
    ++idx;
  }
}

void NluContextSplit::SplitBySyntax_(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  std::vector<std::shared_ptr<basic::NluContext>> branches;
  branches.resize(kMaxNumBranches, nullptr);

  auto context = std::make_shared<milkie::Context>(nluContext);
  auto errCode = feNluContextSplit_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return;
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
      nluContexts.Clear();
      ERROR("unknown_syntax_tag[" << syntaxTag << "]");
      return;
    }

    auto storageItems = storageKv.second->Get();
    for (auto &storageItem : storageItems) {
      basic::Chunk chunk(
              *nluContext,
              syntaxTag,
              storageItem.GetOffset(),
              storageItem.GetContent().length(),
              970);
      if (branches[index]->Add(chunk)) {
        if (basic::SyntaxTag::Type::kStc == syntaxTag) {
          return;
        }
      }
    }
  }

  for (size_t i=0; i<kMaxNumBranches; ++i) {
    if (nullptr != branches[i]) {
      nluContexts.Add(branches[i]);
    }
  }
}

void NluContextSplit::AdjustSegTags_(
        const basic::NluContext &nluContext,
        size_t i,
        basic::PosTag::Type::Val posTag) {
  auto iterSeg = nluContext.GetSegments().GetAll().begin();
  size_t idx=0;
  while (iterSeg != nluContext.GetSegments().GetAll().end()) {
    if (idx == i) {
      (*iterSeg)->SetTag(posTag);
      break;
    }
    ++iterSeg;
    ++idx;
  }
}

}}}
