#pragma once

#include "../public.h"
#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class RuleSyntaxArg : public Rule {
 public:
  virtual bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

 protected:
  virtual bool Filter_(const std::shared_ptr<basic::NluContext> &nluContext) = 0;
  virtual bool ChunkFilter_(const std::shared_ptr<basic::Chunk> &chunk) = 0;
  virtual void AddChunks_(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          const std::shared_ptr<basic::Chunk> &chunk,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) = 0;

 protected:
  size_t offset_;
  size_t len_;
  const basic::Segment &segment_;
};

}}}
