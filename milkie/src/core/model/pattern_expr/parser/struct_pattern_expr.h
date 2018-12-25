#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPatternExpr :public StructElement {
 public: 
  StructPatternExpr(
      const std::wstring &statement,
      const std::shared_ptr<Pattern> &pattern,
      const std::shared_ptr<PatternSet> &patternSet,
      const std::shared_ptr<PatternExpr> &patternExpr,
      const PatternExprs &items,
      const std::wstring &storage,
      PatternExpr::Category categoryPatternExpr);
  
  StructPatternExpr(
      const std::wstring &statement, 
      std::shared_ptr<Pattern> &pattern);

  StructPatternExpr(
      const std::wstring &statement, 
      std::shared_ptr<PatternSet> &patternSet);

  StructPatternExpr(
      const std::wstring &statement, 
      std::shared_ptr<PatternExpr> &patternExpr);

 private:
  std::shared_ptr<Pattern> pattern_;
  std::shared_ptr<PatternSet> patternSet_;
  std::shared_ptr<PatternExpr> patternExpr_;
  const PatternExprs patternExprs_;
  const std::wstring storage_;
  PatternExpr::Category categoryPatternExpr_;
};  

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement,
    const std::shared_ptr<Pattern> &pattern,
    const std::shared_ptr<PatternSet> &patternSet,
    const std::shared_ptr<PatternExpr> &patternExpr,
    const PatternExprs &items,
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
    std::shared_ptr<Pattern> &pattern) :
  StructPatternExpr(statement, pattern, NULL, NULL, NULL, ) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    std::shared_ptr<PatternSet> &patternSet);

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    std::shared_ptr<PatternExpr> &patternExpr);



}}}
