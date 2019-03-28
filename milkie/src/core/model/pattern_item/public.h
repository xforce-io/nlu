#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

struct CategoryPatternItem {
 public:
  enum Category {
    kReg,
    kPos,
    kChunk,
    kDep,
    kInvalid
  };
};

}}}
