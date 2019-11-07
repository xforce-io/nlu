#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RuleSyntaxRule : public Rule {
 private:
  static const size_t kMaxNumBranches = 3;
  static const std::wstring kBranch0SyntaxStoragePrefix;
  static const std::wstring kBranch1SyntaxStoragePrefix;
  static const std::wstring kBranch2SyntaxStoragePrefix;

 public:
  explicit RuleSyntaxRule(std::shared_ptr<milkie::FeatureExtractor> &featureExtractor);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxRule; }
  const char* GetRepr() const;

  virtual bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  void GenForbid(std::vector<ForbidItem> &forbidItems) const;
  bool PreCheckForbid(const ForbidItem&) const { return false; }
  bool PostCheckForbid(const ForbidItem &forbidItem) const;

  virtual Rule* Clone();

 private:
  std::shared_ptr<milkie::FeatureExtractor> featureExtractor_;
  std::shared_ptr<milkie::Context> context_;
};

}}}
