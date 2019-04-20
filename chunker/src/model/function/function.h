#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace chunker {

class Function {
 public:
  virtual void Process(
          const milkie::StorageItem &storageItem,
          basic::NluContext &nluContext) = 0;
};

}}}
