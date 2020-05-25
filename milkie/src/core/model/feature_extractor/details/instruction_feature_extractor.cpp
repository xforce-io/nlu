#include "../instruction_feature_extractor.h"

namespace xforce { namespace nlu { namespace milkie {

InstructionFeatureExtractor::InstructionFeatureExtractor(
    const std::string &name,
    CategoryInstruction::Type categoryInstruction,
    std::shared_ptr<PatternExpr> patternExpr,
    MatchType::Type matchType) :
  name_(name),
  categoryInstruction_(categoryInstruction),
  patternExpr_(patternExpr),
  matchType_(matchType) {}

InstructionFeatureExtractor::InstructionFeatureExtractor(
        const std::string &name,
    std::shared_ptr<PatternExpr> patternExpr,
    MatchType::Type matchType) :
  InstructionFeatureExtractor(
      name,
      CategoryInstruction::kPatternExpr,
      patternExpr,
      matchType) {}

}}}