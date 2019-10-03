#include "../rule_syntax_verb_arg.h"
#include "../../public.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxVerbArg::RuleSyntaxVerbArg(
        size_t offset,
        size_t len,
        const basic::Segment &segment) :
    offset_(offset),
    len_(len),
    segment_(segment) {}

bool RuleSyntaxVerbArg::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  std::wstring query = segment_.GetQuery(nluContext->GetQuery());
  bool isArgTi, isArgWei, isArgZhun;
  bool ret = basic::Manager::Get().GetGkb().GetGkbVerb().TiWeiZhun(
          query,
          isArgTi,
          isArgWei,
          isArgZhun);
  if (!ret || (!isArgTi && !isArgZhun) || isArgWei) {
    return false;
  }

  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetOffset() < offset_+len_) {
      continue;
    }

    if (chunk->GetTag() == basic::SyntaxTag::Type::kNp ||
        chunk->GetTag() == basic::SyntaxTag::Type::kContNp) {
      basic::Chunk newChunk(
              *nluContext,
              basic::SyntaxTag::Type::kNp,
              offset_+len_,
              chunk->GetEnd() - offset_ - len_,
              950);
      newChunk.SetNeedToVerify(true);

      auto newNluContext = Rule::Clone(splitStage, nluContext);
      if (newNluContext->GetChunks().Add(newChunk)) {
        nluContexts.push_back(newNluContext);
        return true;
      }
    }
    return false;
  }
  return true;
}

Rule* RuleSyntaxVerbArg::Clone() {
  return new RuleSyntaxVerbArg(offset_, len_, segment_);
}


}}}
