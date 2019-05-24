#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategyOnlyPredOrPrep : public Strategy {
 public:
  void Process(basic::NluContext &nluContext);

 private:
  inline bool PosFilter_(basic::PosTag::Type posTag);
};

bool StrategyOnlyPredOrPrep::PosFilter_(basic::PosTag::Type posTag) {
  return posTag == basic::PosTag::kA ||
      posTag == basic::PosTag::kV ||
      posTag == basic::PosTag::kP;
}

}}}
