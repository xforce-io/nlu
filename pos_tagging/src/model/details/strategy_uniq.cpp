#include "../strategy_uniq.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyUniq::Process(basic::NluContext &nluContext) {
  auto &clause = nluContext.GetQuery();
  basic::Segment::Set &segments = nluContext.GetSegments();
  for (auto &segment : segments.GetAll()) {
    auto segmentStr = segment.GetStrFromSentence(clause);
    auto poses = basic::Manager::Get().GetGkb().GetGkbGlobal().GetPosTags(segmentStr);
    if (poses != nullptr && poses->size() == 1) {
      SetPos(*segment, (*poses)[0], kStrategyUniq);
    }
  }
}

}}}
