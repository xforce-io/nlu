#pragma once

#include "rule_syntax_arg.h"

namespace xforce { namespace nlu { namespace charles {

class RuleSyntaxRpArg : public RuleSyntaxArg {
 private:
  typedef RuleSyntaxArg Super;

 public:
  explicit RuleSyntaxRpArg(
          size_t offset,
          size_t len,
          const basic::Segment &segment);

  size_t GetCategory() const { return Rule::kCategoryRuleSyntaxRpArg; }
  const char* GetRepr() const;

  Rule* Clone();

protected:
  virtual bool Filter_(const std::shared_ptr<basic::NluContext> &nluContext);
  virtual bool ChunkFilter_(const std::shared_ptr<basic::Chunk> &chunk);
  virtual void AddChunks_(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          const std::shared_ptr<basic::Chunk> &chunk,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);
};

}}}
