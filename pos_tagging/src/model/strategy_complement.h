#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategyComplement : public Strategy {
 public:
  bool Init() { return true; }
  void Process(basic::NluContext &nluContext);
};

}}}
