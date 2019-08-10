#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class RuleSyntaxPrep : public Rule {
 public:
  explicit RuleSyntaxPrep(size_t idx);

  virtual bool Split(
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

 private:
  size_t idxPrep_;
};

}}}
