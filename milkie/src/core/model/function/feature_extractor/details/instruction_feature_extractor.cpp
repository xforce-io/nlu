#include "../instruction_feature_extractor.h"

namespace xforce { namespace nlu { namespace milkie {

InstructionFeatureExtractor::InstructionFeatureExtractor(
    std::shared_ptr<PatternExpr> patternExpr) :
  patternExpr_(patternExpr) {}

}}}