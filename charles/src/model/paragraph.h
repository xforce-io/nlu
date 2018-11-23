#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Sentence;  

class Paragraph {
 public:
  void Process(); 

 private: 
  std::vector<Sentence*> sentences_; 
};

}}
