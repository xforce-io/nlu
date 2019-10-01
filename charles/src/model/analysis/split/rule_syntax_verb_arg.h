#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RuleSyntaxVerbArg : public Rule {
 public:
  explicit RuleSyntaxVerbArg(
          size_t offset,
          size_t len);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxVerbArg; }

  bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  bool GenForbid(ForbidItem &forbidItem) const { return false; }
  bool PreCheckForbid(const ForbidItem &forbidItem) const { return false; }
  bool PostCheckForbid(const ForbidItem&) const { return false; }

  virtual Rule* Clone();

 private:
  size_t offset_;
  size_t len_;
};

}}}
