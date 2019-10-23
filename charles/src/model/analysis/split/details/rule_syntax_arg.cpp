#include "../rule_syntax_arg.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxArg::RuleSyntaxArg(
        size_t offset,
        size_t len,
        const basic::Segment &segment) :
    offset_(offset),
    len_(len),
    segment_(segment) {}

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

bool RuleSyntaxArg::GenForbid(ForbidItem &forbidItem) const {
  forbidItem.SetCategoryRule(GetCategory());
  forbidItem.SetOffset(offset_);
  forbidItem.SetLen(len_);
  return true;
}

bool RuleSyntaxArg::PreCheckForbid(const ForbidItem &forbidItem) const {
  return forbidItem.GetCategoryRule() == GetCategory() &&
      forbidItem.GetOffset() == offset_ &&
      forbidItem.GetLen() == len_;
}

}}}