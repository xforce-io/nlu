#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisComponent {
 public:
  virtual bool Init() { return true; }
  virtual void Dump(JsonType &jsonType) = 0;
};

}}}
