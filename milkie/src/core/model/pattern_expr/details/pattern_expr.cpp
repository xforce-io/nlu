#include "../pattern_expr.h"
#include "../parser/struct_pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

PatternExpr::PatternExpr(
    const Pattern *pattern, 
    const PatternSet *patternSet, 
    const std::wstring *wildcardName,
    const StructPatternExpr *structPatternExpr) {
  if (nullptr == pattern ||
      nullptr == patternSet ||
      nullptr == wildcardName) {
    return;
  }

  if (structPatternExpr->GetPattern() != nullptr) {
    pattern_ = structPatternExpr_->GetPattern();
    return;
  } else if (structPatternExpr->GetPatternSet() != nullptr) {
    patternSet_ = structPatternExpr_->GetPatternSet();
    return;
  }

  if (structPatternExpr->GetItems() != nullptr) {
    items_ = *(structPatternExpr_->GetItems());
  }

  if (nullptr != structPatternExpr_) {
    storage_ = structPatternExpr_->GetStorage();
    repeatPattern_ = structPatternExpr_->GetCategoryPatternExpr();
  }
}

}}}
