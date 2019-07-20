#include "../nlu_context_split.h"

namespace xforce { namespace nlu { namespace charles {

NluContextSplit::NluContextSplit() :
  splitRuleEngine_(nullptr) {}

NluContextSplit::~NluContextSplit() {
  XFC_DELETE(splitRuleEngine_)
}

bool NluContextSplit::Init() {
  bool ret = splitRuleEngine_->Init(Conf::Get().Get());
  if (!ret) {
    FATAL("fail_init[milkie]");
    return false;
  }
  return true;
}

bool NluContextSplit::Split(
        const basic::NluContext &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
        basic::Stage::Val stage) {
  switch (stage) {
    case basic::Stage::Val::kSegment : {
      return SplitBySegment_(nluContext, nluContexts);
    }
    default : {
      break;
    }
  }
  return false;
}

bool NluContextSplit::SplitBySegment_(
        const basic::NluContext &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  auto iterSeg = nluContext.GetSegments().GetAll().begin();
  size_t idx=0;
  while (iterSeg != nluContext.GetSegments().GetAll().end()) {
    if ((*iterSeg)->GetTags().size() > 1) {
      for (auto tag : ((*iterSeg)->GetTags())) {
        auto newNluContext = nluContext.Clone();
        AdjustSegTags_(*newNluContext, idx, tag);
        nluContexts.push_back(newNluContext);
      }
      return true;
    }
    ++iterSeg;
    ++idx;
  }
  return false;
}

bool NluContextSplit::SplitBySyntax_(
        const basic::NluContext &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {

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
