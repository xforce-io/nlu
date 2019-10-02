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
  basic::Manager::Get().GetGkb().GetGkbVerb().TiWeiZhun()
  if ()
  return true;
}

Rule* RuleSyntaxVerbArg::Clone() {
  return new RuleSyntaxVerbArg(offset_, len_, segment_);
}


}}}
