#include "../rule_syntax_arg.h"
#include "../forbid_item.h"
#include "../forbid_mgr.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxArg::RuleSyntaxArg(
        size_t offset,
        size_t len,
        const basic::Segment &segment) :
    Rule(offset, len),
    segment_(segment) {}

void RuleSyntaxArg::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        CollectionNluContext &nluContexts) {
  if (!Filter_(nluContext)) {
    return;
  }

  for (auto &chunk : nluContext->Get<basic::Chunk>().GetAll()) {
    if (chunk->GetOffset() < offset_+len_) {
      continue;
    }

    if (!ChunkFilter_(chunk)) {
      continue;
    }
    AddChunks_(splitStage, nluContext, chunk, nluContexts);
  }
}

void RuleSyntaxArg::GenForbid(std::vector<ForbidItem> &forbidItems) const {
  ForbidItem forbidItem;
  forbidItem.SetCategoryRule(GetCategory());
  forbidItem.SetOffset(offset_);
  forbidItem.SetLen(len_);
  forbidItems.push_back(forbidItem);
}

bool RuleSyntaxArg::PreCheckForbid(const ForbidItem &forbidItem) const {
  return forbidItem.GetCategoryRule() == GetCategory() &&
      forbidItem.GetOffset() == offset_ &&
      forbidItem.GetLen() == len_;
}

}}}
