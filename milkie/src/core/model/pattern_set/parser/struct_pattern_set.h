#pragma once

#include "../public.h"
#include "../../struct_element.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr;
class PatternExprs;

class StructPatternSet :public StructElement {
 public: 
  inline StructPatternSet(
      const std::wstring &statement,
      const std::unordered_set<std::wstring> *patternStrs,
      const PatternExprs *patternExprs);

  inline const std::unordered_set<std::wstring>* GetPatternStrs() const;
  inline const PatternExprs* GetPatternExprs() const;

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
  const PatternExprs *patternExprs_;
};

StructPatternSet::StructPatternSet(
      const std::wstring &statement,
      const std::unordered_set<std::wstring> *patternStrs,
      const PatternExprs *patternExprs) :
  StructElement(statement),
  patternStrs_(patternStrs),
  patternExprs_(patternExprs) {}

const std::unordered_set<std::wstring>* StructPatternSet::GetPatternStrs() const {
  return patternStrs_;
}

const PatternExprs* StructPatternSet::GetPatternExprs() const {
  return patternExprs_;
}

}}}
