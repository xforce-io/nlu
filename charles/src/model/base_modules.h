#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class BaseModules {
 public:
  static bool Init(const xforce::JsonType &conf);
};

}}}
