#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategyLen1 : public Strategy {
 public:
  void Process(basic::NluContext &nluContext);
};

}}}