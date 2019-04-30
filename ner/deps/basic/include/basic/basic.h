#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace basic {

class Basic {
 public:
  static bool Init(const xforce::JsonType &confPos);
  static void Tini() {}
};

}}}
