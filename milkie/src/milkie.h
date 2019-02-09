#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Milkie {
 public:
  static bool Init(const std::string &confpath);
  static void Tini();
};

}}}
