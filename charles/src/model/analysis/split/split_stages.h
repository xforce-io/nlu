#pragma once

#include "../public.h"
#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStages {
 public:
  SplitStages() {}
  virtual ~SplitStages();

  bool Init();


 private:
  bool InitSyntax_();

 private:
  std::list<Rule*> posTag_;

  milkie::Milkie *splitRuleEngine_;
  std::list<Rule*> syntax_;
};

}}}
