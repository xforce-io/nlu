#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisComponent {
 public: 
  virtual void Dump(JsonType &jsonType) = 0;
};

}}}
