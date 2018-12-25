#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternExpr {
 public:  
  enum Category {
    kOnce,
    kZeroOrOnce,
    kZeroOrMore, 
    kOnceOrMore,
  }; 


};  

}}}
