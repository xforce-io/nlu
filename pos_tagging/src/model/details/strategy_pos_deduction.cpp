#include "../strategy_pos_deduction.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyPosDeduction::Process(basic::NluContext &nluContext) {
  Strategy::Process(nluContext);

  typename basic::Segment::Set &segments = nluContext.GetSegments();
  for (auto iter = segments.Begin(); iter != segments.End(); ++iter) {
    ProcessAdverb_(nluContext, segments, iter);
  }
}

void StrategyPosDeduction::ProcessAdverb_(
        basic::NluContext &nluContext,
        basic::Segment::Set &segments,
        basic::Segment::Set::Iter curIter) {
  if (curIter == segments.End()) {
    return;
  }

  auto nextIter = curIter;
  ++nextIter;
  if (nextIter == segments.End()) {
    return;
  }

  auto cur = *curIter;
  if ((cur->SizeTags() == 1 &&
               cur->GetTag() == basic::PosTag::Type::kD) ||
      (cur->SizeTags() > 1 &&
          cur->ContainTag(basic::PosTag::Type::kD))) {
    const std::wstring &curQuery = cur->GetQuery(nluContext.GetQuery());
    if (basic::Manager::Get().GetGkb().GetGkbAdv().beforeSbv(curQuery) == 0) {
      auto afterNextIter = nextIter;
      ++afterNextIter;
      while (afterNextIter != segments.GetAll().end()) {
        for (auto &posTag : (*afterNextIter)->GetTags()) {
          if (basic::PosTag::IsPredicate(posTag)) {
            return;
          }
        }
        ++afterNextIter;
      }
    }

    if ((*curIter)->SizeTags() == 1) {
      if ((*nextIter)->SizeTags() > 1) {
        for (auto &posTag : (*nextIter)->GetTags()) {
          if (posTag != basic::PosTag::Type::kV &&
              posTag != basic::PosTag::Type::kA) {
            (*nextIter)->RemoveTag(posTag);
          }
        }
      }
    } else {
      if ((*nextIter)->SizeTags() == 1 &&
          (*nextIter)->GetTag() != basic::PosTag::Type::kV &&
          (*nextIter)->GetTag() != basic::PosTag::Type::kA) {
        cur->RemoveTag(basic::PosTag::Type::kD);
      }
    }
  }
}

}}}
