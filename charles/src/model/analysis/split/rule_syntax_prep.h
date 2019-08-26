#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class RuleSyntaxPrep : public Rule {
 public:
  explicit RuleSyntaxPrep(
          const std::wstring &prep,
          size_t offset,
          size_t len);

  virtual bool Split(
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  virtual Rule* Clone();

private:
  bool AddNewChunk_(
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
          size_t length,
          uint32_t strategy);

 private:
  std::wstring prep_;
  size_t offsetPrep_;
  size_t lenPrep_;
};

}}}
