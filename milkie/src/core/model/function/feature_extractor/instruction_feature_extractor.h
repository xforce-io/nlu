#pragma once

#include "../../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr;

class InstructionFeatureExtractor {
 public:
  InstructionFeatureExtractor(
          std::shared_ptr<PatternExpr> patternExpr
          );

  std::shared_ptr<PatternExpr> GetPatternExpr() { return patternExpr_; }

 private:
  std::shared_ptr<PatternExpr> patternExpr_;
};

}}}
