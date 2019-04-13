#include "../strategy_uniq.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyUniq::Process(basic::NluContext &nluContext) {
  auto &clause = nluContext.GetQuery();
  typename basic::Segment::Set &segments = nluContext.GetSegments();
  for (size_t i=0; i < segments.Size(); ++i) {
    auto const &segment = segments[i];
    auto poses = basic::Manager::Get().GetGkbZk().GetPos(segment->GetStrFromSentence(clause));
    if (poses != nullptr && poses->size() == 1) {
      segment->SetPosTag((*poses)[0]);
      segment->SetStrategy(Strategy::kStrategyUniq);
    }
  }
}

}}}
