#include "../strategy_uniq.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyUniq::Process(basic::NluContext &nluContext) {
  auto &clause = nluContext.GetQuery();
  typename basic::Segment::Set &segments = nluContext.GetSegments();
  for (size_t i=0; i < segments.Size(); ++i) {
    auto &segment = segments[i];
    auto segmentStr = segment->GetStrFromSentence(clause);
    auto poses = basic::Manager::Get().GetGkbZk().GetPos(segmentStr);
    if (poses != nullptr && poses->size() == 1) {
      SetPos(segment, (*poses)[0], kStrategyUniq);
    }
  }
}

}}}
