#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RulePosTagMultiTag : public Rule {
 public:
  explicit RulePosTagMultiTag(size_t offset);

  size_t GetCategory() const { return Rule::kCategoryRulePosTag; }

  bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  bool GenForbid(ForbidItem &forbidItem) const { return false; }
  bool PreCheckForbid(const ForbidItem &forbidItem) const { return false; }
  bool PostCheckForbid(const ForbidItem &forbidItem) const { return false; }

  virtual Rule* Clone();

 private:
  void AdjustSegTags_(
          const basic::NluContext &nluContext,
          size_t i,
          basic::PosTag::Type::Val posTag);

 private:
  size_t offsetMultiTag_;
};

}}}
