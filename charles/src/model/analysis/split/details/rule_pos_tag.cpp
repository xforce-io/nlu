#include "../rule_pos_tag.h"

namespace xforce { namespace nlu { namespace charles {

bool RulePosTagMultiTag::Split(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  auto iterSeg = nluContext->GetSegments().GetAll().begin();
  size_t idx=0;
  while (iterSeg != nluContext->GetSegments().GetAll().end()) {
    if ((*iterSeg)->GetTags().size() > 1) {
      for (auto tag : ((*iterSeg)->GetTags())) {
        auto newNluContext = nluContext->Clone();
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
