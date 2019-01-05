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
      std::shared_ptr<Pattern> pattern,
      std::shared_ptr<PatternSet> patternSet,
      std::shared_ptr<PatternExpr> patternExpr,
      const PatternExpr::Vector *items,
      const std::wstring *storage,
      CategoryPatternExpr::Category categoryPatternExpr);
  
  StructPatternExpr(
      const std::wstring &statement, 
      std::shared_ptr<Pattern> &pattern);

  StructPatternExpr(
      const std::wstring &statement, 
      std::shared_ptr<PatternSet> &patternSet);

  StructPatternExpr(
      const std::wstring &statement, 
      std::shared_ptr<PatternExpr> &patternExpr);

  virtual ~StructPatternExpr();

  std::shared_ptr<Pattern> GetPattern() const { return pattern_; }
  std::shared_ptr<PatternSet> GetPatternSet() const { return patternSet_; }
  std::shared_ptr<PatternExpr> GetPatternExpr() const { return patternExpr_; }
  const PatternExpr::Vector* GetItems() const { return patternExprs_; }
  const std::wstring* GetStorage() const { return storage_; }
  CategoryPatternExpr::Category GetCategoryPatternExpr() const { return categoryPatternExpr_; }

  static std::shared_ptr<StructPatternExpr> Parse(const std::wstring &blockKey, const std::wstring &statement);

 private:
  std::shared_ptr<Pattern> pattern_;
  std::shared_ptr<PatternSet> patternSet_;
  std::shared_ptr<PatternExpr> patternExpr_;
  PatternExpr::Vector *patternExprs_;
  std::wstring *storage_;
  CategoryPatternExpr::Category categoryPatternExpr_;
};  

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement,
    std::shared_ptr<Pattern> pattern,
    std::shared_ptr<PatternSet> patternSet,
    std::shared_ptr<PatternExpr> patternExpr,
    const PatternExpr::Vector *items,
    const std::wstring *storage,
    CategoryPatternExpr::Category categoryPatternExpr) :
      StructElement(statement),
      pattern_(pattern),
      patternSet_(patternSet),
      patternExpr_(patternExpr),
      patternExprs_(nullptr),
      storage_(nullptr),
      categoryPatternExpr_(categoryPatternExpr) {
  if (nullptr != items) {
    patternExprs_ = new PatternExpr::Vector(*items);
  }

  if (nullptr != storage) {
    storage_ = new std::wstring(*storage);
  }
}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement,
    std::shared_ptr<Pattern> &pattern) :
  StructPatternExpr(statement, pattern, nullptr, nullptr, nullptr, nullptr, CategoryPatternExpr::kNone) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    std::shared_ptr<PatternSet> &patternSet) :
  StructPatternExpr(statement, nullptr, patternSet, nullptr, nullptr, nullptr, CategoryPatternExpr::kNone) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    std::shared_ptr<PatternExpr> &patternExpr) :
  StructPatternExpr(statement, nullptr, nullptr, patternExpr, nullptr, nullptr, CategoryPatternExpr::kNone) {}

}}}
