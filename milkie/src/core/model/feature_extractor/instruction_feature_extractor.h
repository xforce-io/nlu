#pragma once

#include "../../../public.h"

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
        kPartlyMatch,
        kOtherMatch
    };
};

class InstructionFeatureExtractor {
 public:
  InstructionFeatureExtractor(
          const std::string &name,
          CategoryInstruction::Type categoryInstruction,
          std::shared_ptr<PatternExpr> patternExpr,
          MatchType::Type matchType);

  InstructionFeatureExtractor(
          const std::string &name,
          std::shared_ptr<PatternExpr> patternExpr,
          MatchType::Type matchType);

  const std::string& GetName() const { return name_; }
  CategoryInstruction::Type GetCategoryInstruction() const { return categoryInstruction_; }
  std::shared_ptr<PatternExpr> GetPatternExpr() const { return patternExpr_; }
  MatchType::Type GetMatchType() const { return matchType_; }

 private:
  std::string name_;
  CategoryInstruction::Type categoryInstruction_;
  std::shared_ptr<PatternExpr> patternExpr_;
  MatchType::Type matchType_;
};

}}}
