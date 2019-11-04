#include "../rule_syntax_rp_arg.h"

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

Rule* RuleSyntaxRpArg::Clone() {
  return new RuleSyntaxRpArg(offset_, len_, segment_);
}

bool RuleSyntaxRpArg::Filter_(const std::shared_ptr<basic::NluContext> &nluContext) {
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
  basic::Chunk argVp(
          *nluContext,
          basic::SyntaxTag::Type::kVp,
          offset_+len_,
          chunk->GetEnd() - offset_ - len_,
          960);
  argVp.SetNeedToVerify(true);

  basic::Chunk newVp(
          *nluContext,
          basic::SyntaxTag::Type::kVp,
          offset_,
          chunk->GetEnd() - offset_,
          961);

  auto newNluContext = Rule::Clone(splitStage, nluContext);
  bool ret0 = newNluContext->Add(argVp);
  bool ret1 = newNluContext->Add(newVp);
  if (ret0 || ret1) {
    nluContexts.push_back(newNluContext);
  }
}

}}}