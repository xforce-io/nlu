#include "../strategy_complement.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyComplement::Process(basic::NluContext &nluContext) {
  auto &clause = nluContext.GetQuery();
  typename basic::Segment::Set &segments = nluContext.GetSegments();
  for (auto segment : segments.GetAll()) {
    if (segment->GetTags().empty()) {
      auto segmentStr = segment->GetStrFromSentence(clause);
      auto poses = basic::Manager::Get().GetGkb().GetGkbGlobal().GetPosTags(segmentStr);
      if (poses != nullptr && poses->size() >= 1) {
        SetPos(*segment, (*poses)[0], kStrategyOther);
        for (size_t i=1; i < poses->size(); ++i) {
          AddPos(*segment, (*poses)[i]);
        }
      }
    }
  }
}

}}}
