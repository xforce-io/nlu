#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategyPosDeduction : public Strategy {
 public:
  void Process(basic::NluContext &nluContext);

 private:
  void ProcessAdverb_(
          basic::NluContext &nluContext,
          basic::Segment::Set &segments,
          size_t i);
};

}}}