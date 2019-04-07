#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategyContextInfer : public Strategy {
 public:
  bool Init();
  void Process(basic::NluContext &nluContext);
};

}}}
