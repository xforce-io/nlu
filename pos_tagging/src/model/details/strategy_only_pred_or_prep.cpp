#include "../strategy_only_pred_or_prep.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyOnlyPredOrPrep::Process(basic::NluContext &nluContext) {
  int idx = -1;
  basic::Segment::Set &segments = nluContext.GetSegments();
  for (size_t i=0; i < segments.Size(); ++i) {
    auto &segment = segments[i];
    if (PosFilter_(segment->GetPosTag())) {
      return;
    } else if (segment->SizePosTags() > 1) {
      for (auto &posTag : segment->GetPosTags()) {
        if (PosFilter_(posTag)) {
          if (idx>=0) {
            return;
          }
          idx = i;
          break;
        }
      }
    }
  }

  if (idx>=0) {
    auto &posTags = segments[idx]->GetPosTags();
    std::vector<basic::PosTag::Type> posTagsToErase;
    for (auto &posTag : posTags) {
      posTagsToErase.push_back(posTag);
    }

    for (auto &posTag : posTagsToErase) {
      posTags.erase(posTag);
    }
  }
}

}}}
