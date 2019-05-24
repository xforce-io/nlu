#include "../strategy_pos_deduction.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyPosDeduction::Process(basic::NluContext &nluContext) {
  auto &clause = nluContext.GetQuery();
  typename basic::Segment::Set &segments = nluContext.GetSegments();
  for (size_t i=0; i < segments.Size(); ++i) {
    ProcessAdverb_(segments, i);
  }
}

void StrategyPosDeduction::ProcessAdverb_(
        basic::Segment::Set &segments,
        size_t idx) {
  if (segments.Size() - 1 == idx) {
    return;
  }

  auto &cur = segments[idx];
  if ((cur->SizePosTags() == 1 &&
          cur->GetPosTag() == basic::PosTag::kD) ||
      (cur->SizePosTags() > 1 &&
          cur->ContainPosTag(basic::PosTag::kD))) {
    bool hasPredAfterward = false;
    for (size_t i = idx+2; i < segments.Size(); ++i) {
      for (auto &posTag : segments[i]->GetPosTags()) {
        if (basic::PosTag::IsPred(posTag)) {
          hasPredAfterward = true;
          break;
        }
      }

      if (hasPredAfterward) {
        break;
      }
    }

    if (hasPredAfterward) {
      return;
    }

    if (cur->SizePosTags() == 1) {
      auto &next = segments[idx+1];
      if (next->SizePosTags() > 1) {
        for (auto &posTag : next->GetPosTags()) {
          if (posTag != basic::PosTag::kV &&
              posTag != basic::PosTag::kA) {
            next->RemovePosTag(posTag);
          }
        }
      }
    } else {
      auto &next = segments[idx+1];
      if (next->SizePosTags() == 1 &&
          next->GetPosTag() != basic::PosTag::kV &&
          next->GetPosTag() != basic::PosTag::kA) {
        cur->RemovePosTag(basic::PosTag::kD);
      }
    }
  }
}

}}}
