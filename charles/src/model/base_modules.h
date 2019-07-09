#pragma once

#include "public.h"
#include "segmentor/segmentor.h"
#include "pos_tagging/pos_tagging.h"

namespace xforce { namespace nlu { namespace charles {

class BaseModules {
 public:
  bool Init(const xforce::JsonType &conf); 
  segmentor::Segmentor& GetSegmentor() { return *segmentor_; }
  pos::PosTagging& GetPosTagging() { return *posTagging_; }
  chunk::Chunker& GetChunker() {}

  static BaseModules& Get() { return *baseModules_; }

 private: 
  segmentor::Segmentor *segmentor_;
  pos::PosTagging *posTagging_;

  static BaseModules *baseModules_;
};

}}}
