#pragma once

#include "rule_syntax_arg.h"

namespace xforce { namespace nlu { namespace charles {

class RuleSyntaxRpArg : public RuleSyntaxArg {
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
