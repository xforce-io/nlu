#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class RulePosTagMultiTag : public Rule {
 public:
  explicit RulePosTagMultiTag(size_t offset);

  virtual bool Split(
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

 private:
  void AdjustSegTags_(
          const basic::NluContext &nluContext,
          size_t i,
          basic::PosTag::Type::Val posTag);

 private:
  size_t offsetMultiTag_;
};

}}}
