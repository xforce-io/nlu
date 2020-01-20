#pragma once

#include "rule.h"
#include "../end_tags.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;
class EndTags;

/*
 * include pos : u,f,r
 * include word : 说，来说，来看，之外，而外，以外，以后，以来，起，外
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

  bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  void GenForbid(std::vector<ForbidItem> &forbidItems) const;
  bool PreCheckForbid(const ForbidItem &forbidItem) const;

  virtual Rule* Clone();

 private:
  bool AddNewChunk_(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
          size_t length,
          size_t subChunkFrom,
          size_t subChunkTo,
          const EndTags &subChunkTag,
          bool phaseCheck,
          uint32_t strategy);

 private:
  EndTags endTagsForNp_;
  EndTags endTagsForVp_;
  EndTags endTagsForPpSub_;

  std::unordered_set<std::wstring> includeWords_;

  std::wstring prep_;
};

}}}
