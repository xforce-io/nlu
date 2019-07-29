#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class RuleSyntaxRule : public Rule {
 private:
  static const size_t kMaxNumBranches = 3;
  static const std::wstring kBranch0SyntaxStoragePrefix;
  static const std::wstring kBranch1SyntaxStoragePrefix;
  static const std::wstring kBranch2SyntaxStoragePrefix;

 public:
  explicit RuleSyntaxRule(std::shared_ptr<milkie::FeatureExtractor> &featureExtractor);

  virtual bool Split(
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

 private:
  std::shared_ptr<milkie::FeatureExtractor> featureExtractor_;
};

}}}
