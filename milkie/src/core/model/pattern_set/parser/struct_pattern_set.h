#pragma once

#include "../../../../public.h"
#include "../../struct_element.h"
#include "../../pattern_expr/pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr;

class StructPatternSet :public StructElement {
 public: 
  inline StructPatternSet(
      const std::wstring &statement,
      const std::unordered_set<std::wstring> *patternStrs,
      const PatternExpr::Vector *patternExprs);

  inline const std::unordered_set<std::wstring>* GetPatternStrs() const;
  inline const PatternExpr::Vector* GetPatternExprs() const;

  static std::shared_ptr<StructPatternSet> Parse(
      const std::wstring &blockKey,
      const std::wstring &statement);

  static std::shared_ptr<StructPatternSet> ParseForStrSet(
      const std::wstring &blockKey,
      const std::wstring &statement);

  static std::shared_ptr<StructPatternSet> ParseForPatternExprSet(
      const std::wstring &blockKey,
      const std::wstring &statement);

 private:
  const std::unordered_set<std::wstring> *patternStrs_;
  const PatternExpr::Vector *patternExprs_;
};

StructPatternSet::StructPatternSet(
      const std::wstring &statement,
      const std::unordered_set<std::wstring> *patternStrs,
      const PatternExpr::Vector *patternExprs) :
  StructElement(statement),
  patternStrs_(patternStrs),
  patternExprs_(patternExprs) {}

const std::unordered_set<std::wstring>* StructPatternSet::GetPatternStrs() const {
  return patternStrs_;
}

const PatternExpr::Vector* StructPatternSet::GetPatternExprs() const {
  return patternExprs_;
}

}}}
