#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategySpecialToken : public Strategy {
 public:
  StrategySpecialToken() {}
  virtual ~StrategySpecialToken() {}

  void Process(basic::NluContext &nluContext);
};

}}}