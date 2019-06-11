#include "../strategy_pos_deduction.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyPosDeduction::Process(basic::NluContext &nluContext) {
  typename basic::Segment::Set &segments = nluContext.GetSegments();
  for (auto iter = segments.GetAll().begin(); iter != segments.GetAll().end(); ++iter) {
    ProcessAdverb_(nluContext, segments, iter);
  }
}

void StrategyPosDeduction::ProcessAdverb_(
        basic::NluContext &nluContext,
        basic::Segment::Set &segments,
        basic::Segment::Set::Iter curIter) {
  if (curIter == segments.GetAll().end()) {
    return;
  }

  auto nextIter = curIter;
  ++nextIter;
  if (nextIter == segments.GetAll().end()) {
    return;
  }

  auto cur = *curIter;
  if ((cur->SizePosTags() == 1 &&
               cur->GetPosTag() == basic::PosTag::Type::kD) ||
      (cur->SizePosTags() > 1 &&
          cur->ContainPosTag(basic::PosTag::Type::kD))) {
    const std::wstring &curQuery = cur->GetQuery(nluContext.GetQuery());
    if (basic::Manager::Get().GetGkb().GetGkbAdv().beforeSbv(curQuery) == 0) {
      auto afterNextIter = nextIter;
      ++afterNextIter;
      while (afterNextIter != segments.GetAll().end()) {
        for (auto &posTag : (*afterNextIter)->GetPosTags()) {
          if (basic::PosTag::IsPredicate(posTag)) {
            return;
          }
        }
        ++afterNextIter;
      }
    }

    if ((*curIter)->SizePosTags() == 1) {
      if ((*nextIter)->SizePosTags() > 1) {
        for (auto &posTag : (*nextIter)->GetPosTags()) {
          if (posTag != basic::PosTag::Type::kV &&
              posTag != basic::PosTag::Type::kA) {
            (*nextIter)->RemovePosTag(posTag);
          }
        }
      }
    } else {
      if ((*nextIter)->SizePosTags() == 1 &&
          (*nextIter)->GetPosTag() != basic::PosTag::Type::kV &&
          (*nextIter)->GetPosTag() != basic::PosTag::Type::kA) {
        cur->RemovePosTag(basic::PosTag::Type::kD);
      }
    }
  }
}

}}}
