#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class Feature {
 public: 
  static const size_t kMaxScore = 100;
  static const size_t kInitScore = 0;

 protected:
  size_t offset_;
  size_t len_; 
  size_t score_;
};

}}}
