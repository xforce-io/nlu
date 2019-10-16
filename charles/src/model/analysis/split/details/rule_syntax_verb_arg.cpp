#include "../rule_syntax_verb_arg.h"
#include "../../public.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxVerbArg::RuleSyntaxVerbArg(
        size_t offset,
        size_t len,
        const basic::Segment &segment) :
    offset_(offset),
    len_(len),
    segment_(segment) {}

const char* RuleSyntaxVerbArg::GetRepr() const {
  std::sprintf(repr_, "ruleSyntaxVerbArg(%ld|%ld)", offset_, len_);
  return repr_;
}

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

    if (chunk->ContainTag(basic::SyntaxTag::Type::kNp) ||
        chunk->ContainTag(basic::SyntaxTag::Type::kContNp)) {
      basic::Chunk newNp(
              *nluContext,
              basic::SyntaxTag::Type::kNp,
              offset_+len_,
              chunk->GetEnd() - offset_ - len_,
              950);
      newNp.SetNeedToVerify(true);

      basic::Chunk newVp(
              *nluContext,
              basic::SyntaxTag::Type::kVp,
              offset_,
              chunk->GetEnd() - offset_,
              950);

      auto newNluContext = Rule::Clone(splitStage, nluContext);
      bool ret0 = newNluContext->Add(newNp);
      bool ret1 = newNluContext->Add(newVp);
      if (ret0 || ret1) {
        nluContexts.push_back(newNluContext);
        continue;
      }
    }
  }
  return true;
}

bool RuleSyntaxVerbArg::GenForbid(ForbidItem& forbidItem) const {
  forbidItem.SetCategoryRule(Rule::kCategoryRuleSyntaxVerbArg);
  forbidItem.SetOffset(offset_);
  forbidItem.SetLen(len_);
  return true;
}

bool RuleSyntaxVerbArg::PreCheckForbid(const ForbidItem& forbidItem) const {
  return forbidItem.GetCategoryRule() == Rule::kCategoryRuleSyntaxVerbArg &&
      forbidItem.GetOffset() == offset_ &&
      forbidItem.GetLen() == len_;
}

Rule* RuleSyntaxVerbArg::Clone() {
  return new RuleSyntaxVerbArg(offset_, len_, segment_);
}

}}}
