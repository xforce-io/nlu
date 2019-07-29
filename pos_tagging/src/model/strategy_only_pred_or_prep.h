#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class StrategyOnlyPredOrPrep : public Strategy {
 public:
  void Process(basic::NluContext &nluContext);

 private:
  inline bool PosFilter_(basic::PosTag::Type::Val posTag);
};

bool StrategyOnlyPredOrPrep::PosFilter_(basic::PosTag::Type::Val posTag) {
  return basic::PosTag::Type::kA == posTag ||
      basic::PosTag::Type::kV == posTag ||
      basic::PosTag::Type::kP == posTag;
}

}}}
