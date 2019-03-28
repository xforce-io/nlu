#include "../instruction_feature_extractor.h"

namespace xforce { namespace nlu { namespace milkie {

InstructionFeatureExtractor::InstructionFeatureExtractor(
    CategoryInstruction::Type categoryInstruction,
    std::shared_ptr<PatternExpr> patternExpr,
    MatchType::Type matchType) :
  categoryInstruction_(categoryInstruction),
  patternExpr_(patternExpr),
  matchType_(matchType) {}

InstructionFeatureExtractor::InstructionFeatureExtractor(
    std::shared_ptr<PatternExpr> patternExpr,
    MatchType::Type matchType) :
  InstructionFeatureExtractor(
      CategoryInstruction::kPatternExpr,
      patternExpr,
      matchType) {}

}}}