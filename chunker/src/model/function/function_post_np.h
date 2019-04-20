#pragma once

#include "../../public.h"
#include "function.h"

namespace xforce { namespace nlu { namespace chunker {

class FunctionPostNp : public Function {
 public:
  void Process(
          const milkie::StorageItem &storageItem,
          basic::NluContext &nluContext);

 private:
};

}}}
