#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class CategoryPatternExpr {
 public:
  enum Category {
    kNone,
    kOnce,
    kZeroOrOnce,
    kZeroOrMore,
    kOnceOrMore,
  };
};

}}}
