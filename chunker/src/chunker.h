#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace chunker {

class Chunker {
 public: 
  static bool Init(const xforce::JsonType &confJson); 

  static void Tini();
};  

}}}
