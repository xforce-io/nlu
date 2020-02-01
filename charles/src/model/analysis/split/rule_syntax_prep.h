#pragma once

#include "rule.h"
#include "../collection_syntax_tag.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;
class CollectionSyntaxTag;

/*
 * include pos : u,f,r
 * include word : 说，起
 * include word append v : 所（u）+ v，给（u）+v
 */
class RuleSyntaxPrep : public Rule {
 public:
  explicit RuleSyntaxPrep(
          const std::wstring &prep,
          size_t offset,
          size_t len);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxPrep; }
  const char* GetRepr() const;

  void Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts);

  void GenForbid(std::vector<ForbidItem> &forbidItems) const;
  bool PreCheckForbid(const ForbidItem &forbidItem) const;

  virtual Rule* Clone();

 private:
  bool AddNewChunk_(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts,
          size_t length,
          size_t subChunkFrom,
          size_t subChunkTo,
          const CollectionSyntaxTag &subChunkTag,
          bool phaseCheck,
          uint32_t strategy);

 private:
  CollectionSyntaxTag endTagsForNp_;
  CollectionSyntaxTag endTagsForVp_;
  CollectionSyntaxTag endTagsForPpSub_;

  std::unordered_set<std::wstring> includeWords_;

  std::wstring prep_;
};

}}}
