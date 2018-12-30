#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr {
 public:  
  enum Category {
    kOnce,
    kZeroOrOnce,
    kZeroOrMore, 
    kOnceOrMore,
  }; 

  PatternExpr(
      const Pattern *pattern, 
      const PatternSet *patternSet, 
      const std::wstring *wildcardName,
      const StructPatternExpr *structPatternExpr);

  inline explicit PatternExpr(const Pattern &pattern);
  inline explicit PatternExpr(const PatternSet &patternSet);
  inline explicit PatternExpr(const std::wstring &wildcardName);
  inline explicit PatternExpr(const StructPatternExpr &structPatternExpr);

 private: 
  const Pattern *pattern_;
  const PatternSet *patternSet_;
  const std::wstring *wildcardName_;
  const StructPatternExpr *structPatternExpr_;

  PatternExprs items_;
  std::wstring storage_;
  Category repeatPattern_;
};  

PatternExpr::PatternExpr(const Pattern &pattern) :
  PatternExpr(&pattern, NULL, NULL, NULL) {}

PatternExpr::PatternExpr(const PatternSet &patternSet) :
  PatternExpr(NULL, &patternSet, NULL, NULL) {}

PatternExpr::PatternExpr(const std::wstring &wildcardName) :
  PatternExpr(NULL, NULL, &wildcardName, NULL) {}

PatternExpr::PatternExpr(const StructPatternExpr &structPatternExpr) :
  PatternExpr(NULL, NULL, NULL, &structPatternExpr) {}

}}}
