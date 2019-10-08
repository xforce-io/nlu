#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RuleSyntaxPrep : public Rule {
 public:
  explicit RuleSyntaxPrep(
          const std::wstring &prep,
          size_t offset,
          size_t len);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxPrep; }
  const char* GetRepr() const;

  bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  bool GenForbid(ForbidItem &forbidItem) const;
  bool PreCheckForbid(const ForbidItem &forbidItem) const;
  bool PostCheckForbid(const ForbidItem&) const { return false; }

  virtual Rule* Clone();

private:
  bool AddNewChunk_(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
          size_t length,
          size_t subChunkFrom,
          size_t subChunkTo,
          basic::SyntaxTag::Type::Val subChunkTag,
          uint32_t strategy);

 private:
  std::wstring prep_;
  size_t offsetPrep_;
  size_t lenPrep_;
};

}}}
