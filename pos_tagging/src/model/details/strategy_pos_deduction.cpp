#include "../strategy_pos_deduction.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyPosDeduction::Process(basic::NluContext &nluContext) {
  typename basic::Segment::Set &segments = nluContext.GetSegments();
  for (size_t i=0; i < segments.Size(); ++i) {
    ProcessAdverb_(nluContext, segments, i);
  }
}

void StrategyPosDeduction::ProcessAdverb_(
        basic::NluContext &nluContext,
        basic::Segment::Set &segments,
        size_t idx) {
  if (segments.Size() - 1 == idx) {
    return;
  }

  auto &cur = segments[idx];
  if ((cur->SizePosTags() == 1 &&
          cur->GetPosTag() == basic::PosTag::Type::kD) ||
      (cur->SizePosTags() > 1 &&
          cur->ContainPosTag(basic::PosTag::Type::kD))) {
    const std::wstring &curQuery = cur->GetQuery(nluContext.GetQuery());
    if (basic::Manager::Get().GetGkb().GetGkbAdv().beforeSbv(curQuery) == 0) {
      for (size_t i = idx + 2; i < segments.Size(); ++i) {
        for (auto &posTag : segments[i]->GetPosTags()) {
          if (basic::PosTag::IsPredicate(posTag)) {
            return;
          }
        }
      }
    }

    if (cur->SizePosTags() == 1) {
      auto &next = segments[idx+1];
      if (next->SizePosTags() > 1) {
        for (auto &posTag : next->GetPosTags()) {
          if (posTag != basic::PosTag::Type::kV &&
              posTag != basic::PosTag::Type::kA) {
            next->RemovePosTag(posTag);
          }
        }
      }
    } else {
      auto &next = segments[idx+1];
      if (next->SizePosTags() == 1 &&
          next->GetPosTag() != basic::PosTag::Type::kV &&
          next->GetPosTag() != basic::PosTag::Type::kA) {
        cur->RemovePosTag(basic::PosTag::Type::kD);
      }
    }
  }
}

}}}
