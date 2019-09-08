#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class Rule {
 public:
  virtual bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) = 0;

  virtual ~Rule() {}

  virtual Rule* Clone() = 0;

 protected:
  static std::shared_ptr<basic::NluContext> Clone(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext);
};

}}}
