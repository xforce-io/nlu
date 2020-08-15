#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class Interface {
 public:
  static bool ParseRaw(
          const std::vector<std::string> flags,
          std::shared_ptr<basic::NluContext> &nluContext);

};

}}}