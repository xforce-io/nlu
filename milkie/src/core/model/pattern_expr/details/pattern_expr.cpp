#include "../pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

PatternExpr::PatternExpr(
    const Pattern *pattern, 
    const PatternSet *patternSet, 
    const std::wstring *wildcardName,
    const StructPatternExpr *structPatternExpr) {
  if (NULL == pattern || 
      NULL == patternSet ||
      NULL == wildcardName) {
    return ;
  }

  if (structPatternExpr->GetPattern())
}

}}}
