#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace ner {

class Ner {
 public: 
  static bool Init(const xforce::JsonType &confJson); 

  static void Tini();
};

}}}
