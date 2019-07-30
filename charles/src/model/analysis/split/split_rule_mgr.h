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

  bool Init();
  const std::vector<Rules*> GetRules() const { return allRules_; }

 private:
  bool InitSyntax_();

 private:
  std::vector<Rules*> allRules_;

  milkie::Milkie *splitRuleEngine_;
};

}}}
