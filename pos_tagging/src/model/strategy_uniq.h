#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategyUniq : public Strategy {
 public:
  void Process(basic::NluContext &nluContext);
};

}}}
