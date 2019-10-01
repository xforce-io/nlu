#include "../rule_syntax_verb_arg.h"
#include "../../public.h"

namespace xforce { namespace nlu { namespace charles {

RuleSyntaxVerbArg::RuleSyntaxVerbArg(
        size_t offset,
        size_t len) :
    offset_(offset),
    len_(len) {}

bool RuleSyntaxVerbArg::Split(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  return true;
}

Rule* RuleSyntaxVerbArg::Clone() {
  return new RuleSyntaxVerbArg(offset_, len_);
}


}}}
