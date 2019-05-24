#include "../strategy_only_pred_or_prep.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyOnlyPredOrPrep::Process(basic::NluContext &nluContext) {
  size_t idx = -1;
  basic::Segment::Set &segments = nluContext.GetSegments();
  for (size_t i=0; i < segments.Size(); ++i) {
    auto &segment = segments[i];
    if (PosFilter_(segment->GetPosTag())) {
      return;
    } else if (segment->SizePosTags() > 1) {
      for (auto &posTag : segment->GetPosTags()) {
        if (PosFilter_(posTag)) {
          if (idx >= 0) {
            return;
          }
          idx = i;
        }
      }
    }
  }

  if (idx>=0) {
    auto &segment = segments[idx];
    auto iter = segment->GetPosTags().begin();
    while (iter != segment->GetPosTags().end()) {
      auto next = iter+1;
      if (!PosFilter_(*iter)) {
        segment->GetPosTags().erase(iter);
      }
      iter = next;
    }
  }
}

}}}
