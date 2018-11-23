#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Segmentor;

class BaseModules {
 public:
  bool Init(); 
  Segmentor& GetSegmentor() { return *segmentor_; } 

  static BaseModules& Get() { return *baseModules_; }

 private: 
  Segmentor *segmentor_; 

  static BaseModules *baseModules_;
};

}}
