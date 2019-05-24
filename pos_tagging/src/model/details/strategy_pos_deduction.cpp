#include "../strategy_pos_deduction.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyPosDeduction::Process(basic::NluContext &nluContext) {
  auto &clause = nluContext.GetQuery();
  typename basic::Segment::Set &segments = nluContext.GetSegments();
  for (size_t i=0; i < segments.Size(); ++i) {

  }
}

void StrategyPosDeduction::ProcessAdverb_(
        basic::Segment::Set &segments,
        size_t i) {
  if (segments.Size() - 1 == i) {
    return;
  }

  auto &cur = segments[i];
  auto &next = segments[i+1];
  if (cur->SizePosTags() == 1 &&
      cur->GetPosTag() == basic::PosTag::kD) {

  } else if (cur->SizePosTags() > 1 &&
      cur->ContainPosTag(basic::PosTag::kD)) {

  }
}

}}}
