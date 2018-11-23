#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Clause;  

class Sentence {
 public:
  void Process(); 
   
 private:
  void Segment_(); 
  void PosTagging_();
  void NerRecognize_();

 private:
   std::vector<Clause*> clauses_; 
};

}}
