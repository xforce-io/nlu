#pragma once

#include "../public.h"
#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class RuleSyntaxArg : public Rule {
 public:
  explicit RuleSyntaxArg(
          size_t offset,
          size_t len,
          const basic::Segment &segment);

  virtual bool Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  virtual void GenForbid(std::vector<ForbidItem> &forbidItems) const;
  virtual bool PreCheckForbid(const ForbidItem &forbidItem) const;

 protected:
  virtual bool ChunkFilter_(const std::shared_ptr<basic::Chunk> &chunk) = 0;
  virtual void AddChunks_(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          const std::shared_ptr<basic::Chunk> &chunk,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) = 0;

 protected:
  const basic::Segment &segment_;
};

}}}
