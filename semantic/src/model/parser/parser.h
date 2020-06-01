#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace semantic {

class Parser {
 public:
  Parser() {} 
  virtual ~Parser() {} 
  inline void Process(basic::NluContext &nluContext);

 protected:
  virtual bool Filter_(basic::NluContext &nluContext) = 0;
  virtual void Process_(basic::NluContext &nluContext) = 0;
};

void Parser::Process(basic::NluContext &nluContext) {
  if (Filter_(nluContext)) {
    Process_(nluContext);
  }
}

}}}
