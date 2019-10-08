#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RuleSyntaxContNp : public Rule {
 public:
  RuleSyntaxContNp(size_t offset, size_t len);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxContNp; }
  const char* GetRepr() const;

  bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  bool GenForbid(ForbidItem &forbidItem) const;
  bool PreCheckForbid(const ForbidItem &forbidItem) const;
  bool PostCheckForbid(const ForbidItem&) const { return false; }

  Rule* Clone();

 private:
  bool AddNewChunk_(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
          size_t offset,
          uint32_t strategy);

 private:
  size_t offset_;
  size_t len_;
};

}}}
