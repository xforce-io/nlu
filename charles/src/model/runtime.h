#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class Runtime {
 public:
  Runtime(); 
  virtual ~Runtime();

  //@return : succ or fail
  bool Process(const std::wstring &query);

 private:  
  bool Round_();

 private: 
  AnalysisContext *currentAnalysisContext_;
};

}}}
