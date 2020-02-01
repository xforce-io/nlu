#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RuleSyntaxVerbArg : public Rule {
 public:
  explicit RuleSyntaxVerbArg(
          size_t offset,
          size_t len,
          const basic::Segment &segment);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxVerbArg; }
  const char* GetRepr() const;

  bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts);

  void GenForbid(std::vector<ForbidItem>& forbidItems) const;
  bool PreCheckForbid(const ForbidItem& forbidItem) const;

  virtual Rule* Clone();

 private:
  const basic::Segment &segment_;
};

}}}
