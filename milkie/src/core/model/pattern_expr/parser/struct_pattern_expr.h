#pragma once

#include "../public.h"
#include "../../struct_element.h"
#include "../pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

class Pattern;
class PatternSet;
class PatternExpr;

class StructPatternExpr :public StructElement {
 public: 
  StructPatternExpr(
      const std::wstring &statement,
      const Pattern *pattern,
      const PatternSet *patternSet,
      const PatternExpr *patternExpr,
      const PatternExprs *items,
      const std::wstring *storage,
      CategoryPatternExpr::Category categoryPatternExpr);
  
  StructPatternExpr(
      const std::wstring &statement, 
      const Pattern &pattern);

  StructPatternExpr(
      const std::wstring &statement, 
      const PatternSet &patternSet);

  StructPatternExpr(
      const std::wstring &statement, 
      const PatternExpr &patternExpr);

  const Pattern* GetPattern() const { return pattern_; }
  const PatternSet* GetPatternSet() const { return patternSet_; }
  const PatternExpr* GetPatternExpr() const { return patternExpr_; }
  const PatternExprs* GetItems() const { return patternExprs_; }
  const std::wstring* GetStorage() const { return storage_; }
  CategoryPatternExpr::Category GetCategoryPatternExpr() const { return categoryPatternExpr_; }

  static std::shared_ptr<StructPatternExpr> Parse(const std::wstring &blockKey, const std::wstring &statement);

 private:
  const Pattern *pattern_;
  const PatternSet *patternSet_;
  const PatternExpr *patternExpr_;
  const PatternExprs *patternExprs_;
  const std::wstring *storage_;
  CategoryPatternExpr::Category categoryPatternExpr_;
};  

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement,
    const Pattern *pattern,
    const PatternSet *patternSet,
    const PatternExpr *patternExpr,
    const PatternExprs *items,
    const std::wstring *storage,
    CategoryPatternExpr::Category categoryPatternExpr) :
  StructElement(statement),
  pattern_(pattern),
  patternSet_(patternSet),
  patternExpr_(patternExpr),
  patternExprs_(items),
  storage_(storage),
  categoryPatternExpr_(categoryPatternExpr) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    const Pattern &pattern) :
  StructPatternExpr(statement, &pattern, nullptr, nullptr, nullptr, nullptr, CategoryPatternExpr::kNone) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    const PatternSet &patternSet) :
  StructPatternExpr(statement, nullptr, &patternSet, nullptr, nullptr, nullptr, CategoryPatternExpr::kNone) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    const PatternExpr &patternExpr) :
  StructPatternExpr(statement, nullptr, nullptr, &patternExpr, nullptr, nullptr, CategoryPatternExpr::kNone) {}

}}}
