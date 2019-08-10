#pragma once

#include "../public.h"
#include "rule.h"
#include "split_stage.h"

namespace xforce { namespace nlu { namespace charles {

class SplitRuleMgr {
 public:
  typedef std::vector<Rule*> Rules;

 public:
  SplitRuleMgr();
  virtual ~SplitRuleMgr();

  bool Init(const basic::NluContext &nluContext);
  const std::vector<Rules*> GetRules() const { return allRules_; }

 private:
  bool InitSyntax_(const basic::NluContext &nluContext);
  bool InitSyntaxFromRules_(const basic::NluContext &nluContext);
  bool InitSyntaxForPrep_(const basic::NluContext &nluContext);

 private:
  std::vector<Rules*> allRules_;
  milkie::Milkie *splitRuleEngine_;
};

}}}
