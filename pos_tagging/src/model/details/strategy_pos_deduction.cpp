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
  auto &segment = segments[i];
  if (segment->GetPosTags().si)
}

}}}
