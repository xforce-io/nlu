#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class CategoryPatternExpr {
 public:
  enum Category {
    kOnce,
    kZeroOrOnce,
    kZeroOrMore,
    kOnceOrMore,
  };
};

}}}
