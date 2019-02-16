#pragma once

#include "../../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr;

struct CategoryInstruction {
    enum Type {
        kFilter,
        kPatternExpr,
    };
};

struct MatchType {
    enum Type {
        kPrefixMatch,
        kExactMatch,
        kOtherMatch
    };
};

class InstructionFeatureExtractor {
 public:
  InstructionFeatureExtractor(
          CategoryInstruction::Type categoryInstruction,
          std::shared_ptr<PatternExpr> patternExpr,
          MatchType::Type matchType);

  InstructionFeatureExtractor(
          std::shared_ptr<PatternExpr> patternExpr,
          MatchType::Type matchType);

  CategoryInstruction::Type GetCategoryInstruction() const { return categoryInstruction_; }
  std::shared_ptr<PatternExpr> GetPatternExpr() const { return patternExpr_; }
  MatchType::Type GetMatchType() const { return matchType_; }

 private:
  CategoryInstruction::Type categoryInstruction_;
  std::shared_ptr<PatternExpr> patternExpr_;
  MatchType::Type matchType_;
};

}}}
