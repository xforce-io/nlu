#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class Clause {
 private:

 public:
  Clause(const std::wstring &clause);

  virtual ~Clause();

 private:
  std::wstring clause_;
};

}}}
