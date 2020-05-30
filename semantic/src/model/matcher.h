#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace semantic {

class Parser;

class Matcher {
 public:
  Matcher();
  virtual ~Matcher();

  bool Init();
  void Match(std::shared_ptr<basic::NluContext> nluContext);

 private:
  milkie::Milkie *ruleEngine_;
  std::list<Parser*> parsers_;
};

}}}