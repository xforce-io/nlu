#include "../rule_syntax_arg.h"

namespace xforce { namespace nlu { namespace charles {

bool RuleSyntaxArg::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  if (!Filter_(nluContext)) {
    return false;
  }

  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetOffset() < offset_+len_) {
      continue;
    }

    if (!ChunkFilter_(chunk)) {
      continue;
    }
    AddChunks_(splitStage, nluContext, chunk, nluContexts);
  }
  return true;
}

}}}