#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RuleSyntaxVerbArg : public Rule {
 public:
  explicit RuleSyntaxVerbArg(
          size_t offset,
          size_t len,
          const basic::Segment &segment,
          const std::wstring &aux);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxVerbArg; }
  const char* GetRepr() const;

  void Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts);

  void GenForbid(std::vector<ForbidItem>& forbidItems) const;
  bool PreCheckForbid(const ForbidItem& forbidItem) const;

  virtual Rule* Clone();

 private:
  basic::SyntaxTag::Type::Val GetFinalSyntaxTag_() const;

 private:
  const basic::Segment &segment_;
  std::wstring aux_;
};

}}}
