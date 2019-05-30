#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace chunker {

class Function {
 public:
  virtual void Process(
          IN const basic::FragmentSet<basic::Segment> &segment,
          OUT basic::FragmentSet<basic::Chunk> &chunks) = 0;
};

}}}
