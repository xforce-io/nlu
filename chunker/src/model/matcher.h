#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher {
 public:
  Matcher();

  bool Init();
  void Match();

  virtual ~Matcher();

 private:
  milkie::Milkie *milkie_;
};

}}}
