#include "../rule_syntax_rp_arg.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxRpArg::RuleSyntaxRpArg(
        size_t offset,
        size_t len,
        const basic::Segment &segment) :
   Super(offset, len, segment) {}

const char* RuleSyntaxRpArg::GetRepr() const {
  std::sprintf(repr_, "ruleSyntaxRpArg(%ld|%ld)", offset_, len_);
  return repr_;
}

void RuleSyntaxRpArg::GenGlobalForbid(std::vector<ForbidItem> &forbidItems) const {
  for (auto &chunk : chunksToVerify_) {
    ForbidItem forbidItem;
    forbidItem.SetCategoryRule(ForbidItem::kCategoryGlobalRuleInterval);
    forbidItem.SetOffset(chunk->GetOffset());
    forbidItem.SetLen(chunk->GetLen());
    forbidItems.push_back(forbidItem);
  }
}

Rule* RuleSyntaxRpArg::Clone() {
  return new RuleSyntaxRpArg(offset_, len_, segment_);
}

bool RuleSyntaxRpArg::Filter_(const std::shared_ptr<basic::NluContext> &nluContext) const {
  UNUSE(nluContext)
  return segment_.GetTag() == basic::PosTag::Type::kRp;
}

bool RuleSyntaxRpArg::ChunkFilter_(const std::shared_ptr<basic::Chunk> &chunk) {
  return chunk->ContainTag(basic::SyntaxTag::Type::kV) ||
      chunk->ContainTag(basic::SyntaxTag::Type::kVp);
}

void RuleSyntaxRpArg::AddChunks_(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        const std::shared_ptr<basic::Chunk> &chunk,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  auto argVp = std::make_shared<basic::Chunk>(
          *nluContext,
          basic::SyntaxTag::Type::kVp,
          offset_+len_,
          chunk->GetEnd() - offset_ - len_,
          960);
  argVp->SetNeedToVerify(GetRepr());
  chunksToVerify_.push_back(argVp);

  std::shared_ptr<basic::Chunk> newVp = nullptr;
  auto segAfter = nluContext->GetSegments().GetFragmentAfter(chunk->GetEnd());
  if (nullptr!=segAfter) {
    auto segQuery = segAfter->GetQuery(nluContext->GetQuery());
    if (L"的" == segQuery) {
      newVp = std::make_shared<basic::Chunk>(
              *nluContext,
              basic::SyntaxTag::Type::kVp,
              offset_,
              chunk->GetEnd() - offset_ + segQuery.length(),
              961);
    }
  }

  if (nullptr == newVp) {
    newVp = std::make_shared<basic::Chunk>(
            *nluContext,
            basic::SyntaxTag::Type::kVp,
            offset_,
            chunk->GetEnd() - offset_,
            961);
  }

  auto newNluContext = Rule::Clone(splitStage, nluContext);
  bool ret0 = newNluContext->Add(argVp);
  bool ret1 = newNluContext->Add(newVp);
  if (ret0 || ret1) {
    nluContexts.push_back(newNluContext);
  }
}

}}}
