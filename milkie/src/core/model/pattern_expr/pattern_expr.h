#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Pattern;
class PatternSet;
class StructPatternExpr;

class PatternExpr {
 public:
  PatternExpr(
      const Pattern *pattern, 
      const PatternSet *patternSet, 
      const std::wstring *wildcardName,
      const StructPatternExpr *structPatternExpr);

  inline explicit PatternExpr(const Pattern &pattern);
  inline explicit PatternExpr(const PatternSet &patternSet);
  inline explicit PatternExpr(const std::wstring &wildcardName);
  inline explicit PatternExpr(const StructPatternExpr &structPatternExpr);

  CategoryPatternExpr GetRepeatPattern() const { return repeatPattern_; }
  inline void SetStorageKey(const std::wstring &storageStored);

 private: 
  const Pattern *pattern_;
  const PatternSet *patternSet_;
  const std::wstring *wildcardName_;
  const StructPatternExpr *structPatternExpr_;

  std::vector<std::shared_ptr<PatternExpr>> items_;
  std::wstring storage_;
  CategoryPatternExpr repeatPattern_;
};

typedef std::vector<std::shared_ptr<PatternExpr>> PatternExprs;

PatternExpr::PatternExpr(const Pattern &pattern) :
  PatternExpr(&pattern, nullptr, nullptr, nullptr) {}

PatternExpr::PatternExpr(const PatternSet &patternSet) :
  PatternExpr(nullptr, &patternSet, nullptr, nullptr) {}

PatternExpr::PatternExpr(const std::wstring &wildcardName) :
  PatternExpr(nullptr, nullptr, &wildcardName, nullptr) {}

PatternExpr::PatternExpr(const StructPatternExpr &structPatternExpr) :
  PatternExpr(nullptr, nullptr, nullptr, &structPatternExpr) {}

void PatternExpr::SetStorageKey(const std::wstring &storageStored) {
}

}}}
