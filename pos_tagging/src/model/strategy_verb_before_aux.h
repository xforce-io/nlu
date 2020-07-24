#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategyVerbBeforeAux : public Strategy {
 public:
  StrategyVerbBeforeAux() {}
  virtual ~StrategyVerbBeforeAux() {}

  void Process(basic::NluContext &nluContext);
};

}}}