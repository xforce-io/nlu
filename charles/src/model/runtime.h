#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisContext;  

class Runtime {
 public:
  Runtime(); 
  virtual ~Runtime();

  //@return : succ or fail
  bool Process(const std::wstring &query);
  void DumpAnalysisContext(JsonType &jsonType);

 private:  
  bool Round_();

 private: 
  AnalysisContext *currentAnalysisContext_;
};

}}}
