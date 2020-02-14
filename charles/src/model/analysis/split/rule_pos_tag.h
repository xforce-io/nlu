#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RulePosTagMultiTag : public Rule {
 public:
  explicit RulePosTagMultiTag(size_t offset);

  size_t GetCategory() const { return Rule::kCategoryRulePosTag; }
  const char* GetRepr() const;

  void Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts);

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
