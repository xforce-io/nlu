#pragma once

#include "public.h"
#include "segmentor/segmentor.h" 

namespace xforce { namespace nlu { namespace charles {

class BaseModules {
 public:
  bool Init(); 
  segmentor::Segmentor& GetSegmentor() { return *segmentor_; } 

  static BaseModules& Get() { return *baseModules_; }

 private: 
  segmentor::Segmentor *segmentor_; 

  static BaseModules *baseModules_;
};

}}}
