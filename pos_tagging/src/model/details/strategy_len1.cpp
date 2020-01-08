#include "../strategy_len1.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyLen1::Process(basic::NluContext &nluContext) {
  Strategy::Process(nluContext);

  if (nluContext.GetSegments().Size() == 1) {
    SetPos(
            **(nluContext.GetSegments().GetAll().begin()),
            basic::PosTag::Type::kN,
            basic::Confidence(basic::Confidence::kFull),
            kStrategyLen1);
  }
}

}}}