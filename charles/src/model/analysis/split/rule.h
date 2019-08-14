#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class Rule {
 public:
  virtual bool Split(
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) = 0;

  virtual ~Rule() {}
};

}}}
