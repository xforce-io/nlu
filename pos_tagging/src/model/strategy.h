#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace pos {

class Strategy {
 public:
  virtual void Process(basic::NluContext &nluContext) = 0;
};

}}}
