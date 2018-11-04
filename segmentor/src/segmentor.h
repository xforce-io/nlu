#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Segmentor {
 public: 
  static bool Init(const std::string &confpath);
  static void Tini();
};

}}

