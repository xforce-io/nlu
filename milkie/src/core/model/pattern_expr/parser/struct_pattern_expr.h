#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPatternExpr :public StructElement {
 public: 
  StructPatternExpr(
      const std::wstring &statement,
      const Pattern *pattern,
      const PatternSet *patternSet,
      const PatternExpr *patternExpr,
      const PatternExprs *items,
      const std::wstring &storage,
      PatternExpr::Category categoryPatternExpr);
  
  StructPatternExpr(
      const std::wstring &statement, 
      Pattern *pattern);

  StructPatternExpr(
      const std::wstring &statement, 
      PatternSet *patternSet);

  StructPatternExpr(
      const std::wstring &statement, 
      PatternExpr *patternExpr);

  const Pattern* GetPattern() const { return pattern_; }
  const PatternSet* GetPatternSet() const { return patternSet_; }
  const PatternExpr* GetPatternExpr() const { return patternExpr_; }
  const PatternExprs* GetItems() const { return patternExprs_; }
  const std::wstring& GetStorage() const { return storage_; }
  PatternExpr::Category GetCategoryPatternExpr() const { return categoryPatternExpr_; }

  static std::shared_ptr<StructPatternExpr> Parse(const std::wstring &blockKey, const std::wstring &statement);

 private:
  const Pattern *pattern_;
  const PatternSet *patternSet_;
  const PatternExpr *patternExpr_;
  const PatternExprs *patternExprs_;
  const std::wstring storage_;
  PatternExpr::Category categoryPatternExpr_;
};  

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement,
    const Pattern *pattern,
    const PatternSet *patternSet,
    const PatternExpr *patternExpr,
    const PatternExprs *items,
    const std::wstring &storage,
    PatternExpr::Category categoryPatternExpr) :
  StructElement(statement),
  pattern_(pattern),
  patternSet_(patternSet),
  patternExpr_(patternExpr),
  patternExprs_(items),
  storage_(storage),
  categoryPatternExpr_(categoryPatternExpr) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    Pattern *pattern) :
  StructPatternExpr(statement, pattern, NULL, NULL, NULL, ) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    PatternSet *patternSet);

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    PatternExpr *patternExpr);

}}}
