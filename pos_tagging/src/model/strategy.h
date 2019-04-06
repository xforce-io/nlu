#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace pos {

class Strategy {
 public:
  Strategy() {}
  virtual ~Strategy();

  virtual bool Init() { return true; }
  virtual void Process(basic::NluContext &nluContext) = 0;
};

}}}
