#include "../rule_pos_tag.h"
#include "../split_stage.h"

namespace xforce { namespace nlu { namespace charles {

RulePosTagMultiTag::RulePosTagMultiTag(size_t offset) :
  offsetMultiTag_(offset) {}

bool RulePosTagMultiTag::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  auto iterSeg = nluContext->GetSegments().GetAll().begin();
  size_t idx=0;
  while (iterSeg != nluContext->GetSegments().GetAll().end()) {
    if ((*iterSeg)->GetOffset() == offsetMultiTag_ && (*iterSeg)->GetTags().size() > 1) {
      for (auto tag : ((*iterSeg)->GetTags())) {
        auto newNluContext = Rule::Clone(splitStage, nluContext);
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

Rule* RulePosTagMultiTag::Clone() {
  return new RulePosTagMultiTag(offsetMultiTag_);
}

void RulePosTagMultiTag::AdjustSegTags_(
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
