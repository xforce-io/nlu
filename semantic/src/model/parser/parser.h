#include "../../public.h"

namespace xforce { namespace nlu { namespace semantic {

class Parser {
 public:
  virtual void Process(basic::NluContext &nluContext) = 0;
};

}}}