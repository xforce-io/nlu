#include "../rule_syntax_verb_arg.h"
#include "../../public.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxVerbArg::RuleSyntaxVerbArg(
        size_t offset,
        size_t len,
        const basic::Segment &segment,
        const std::wstring &aux) :
    Rule(offset, len),
    segment_(segment),
    aux_(aux) {}

const char* RuleSyntaxVerbArg::GetRepr() const {
  std::sprintf(repr_, "ruleSyntaxVerbArg(%ld|%ld)", offset_, len_);
  return repr_;
}

void RuleSyntaxVerbArg::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        CollectionNluContext &nluContexts) {
  std::wstring query = segment_.GetQuery(nluContext->GetQuery());
  bool isArgTi, isArgWei, isArgZhun;
  bool ret = basic::Manager::Get().GetGkb().GetGkbVerb().TiWeiZhun(
          query,
          isArgTi,
          isArgWei,
          isArgZhun);
  if (!ret || (!isArgTi && !isArgZhun)) {
    return;
  }

  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetOffset() < offset_+len_) {
      continue;
    }

    if (chunk->ContainTag(basic::SyntaxTag::Type::kNp) ||
        chunk->ContainTag(basic::SyntaxTag::Type::kContNp)) {
      auto newNluContext = Rule::Clone(splitStage, nluContext);
      newNluContext->AddPhrase(
              GetEnd(),
              chunk->GetEnd() - GetEnd(),
              std::make_shared<basic::CollectionSyntaxTag>(basic::SyntaxTag::Type::kNp),
              950);

      basic::Chunk newChunk(
              *nluContext,
              GetFinalSyntaxTag_(),
              offset_,
              chunk->GetEnd() - offset_,
              951);

      bool ret0 = newNluContext->Add(newChunk);
      if (ret0) {
        nluContexts.Add(newNluContext);
        continue;
      }
    }
  }

  if (!nluContexts.Empty()) {
    nluContexts.Add(nluContext->Clone());
  }
}

void RuleSyntaxVerbArg::GenForbid(std::vector<ForbidItem> &forbidItems) const {
  ForbidItem forbidItem;
  forbidItem.SetCategoryRule(GetCategory());
  forbidItem.SetOffset(offset_);
  forbidItem.SetLen(len_);
  forbidItems.push_back(forbidItem);
}

bool RuleSyntaxVerbArg::PreCheckForbid(const ForbidItem& forbidItem) const {
  return forbidItem.GetCategoryRule() == GetCategory() &&
      forbidItem.GetOffset() == offset_ &&
      forbidItem.GetLen() == len_;
}

Rule* RuleSyntaxVerbArg::Clone() {
  return new RuleSyntaxVerbArg(
      offset_,
      len_,
      segment_,
      aux_);
}

basic::SyntaxTag::Type::Val RuleSyntaxVerbArg::GetFinalSyntaxTag_() const {
  if (L"的" == aux_) {
    return basic::SyntaxTag::Type::kNp;
  } else {
    return basic::SyntaxTag::Type::kVp;
  }
}

}}}
