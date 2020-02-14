#pragma once

#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class RuleSyntaxContNp : public Rule {
 public:
  RuleSyntaxContNp(size_t offset, size_t len);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxContNp; }
  const char* GetRepr() const;

  void Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts);

  void GenForbid(std::vector<ForbidItem> &forbidItems) const;
  bool GlobalCheckForbid(const ForbidItem&) const;
  bool PreCheckForbid(const ForbidItem &forbidItem) const;

  Rule* Clone();

 private:
    bool Filter_(const std::shared_ptr<basic::NluContext> &nluContext) const;
    void AddNewChunk_(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts,
          size_t offset,
          uint32_t strategy);
};

}}}
