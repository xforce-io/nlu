#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Conf {
 public: 
  Conf();

  bool Init(const std::string &filedir); 
};

}}
