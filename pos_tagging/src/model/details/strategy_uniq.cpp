#include "../strategy_uniq.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyUniq::Process(basic::NluContext &nluContext) {
  auto &clause = nluContext.GetQuery();
  auto &segments = nluContext.GetSegments();
  for (size_t i=0; i < segments.Size(); ++i) {
    auto &segment = segments[i];
    auto poses = basic::Manager::Get().GetGkbZk().GetPos(*(segment->GetStr()));
    if (poses->size() == 1) {
      segment->SetPosTag((*poses)[0]);
    }
  }
}

}}}
