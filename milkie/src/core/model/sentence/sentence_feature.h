#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class NluContext;  

class SentenceFeature {
 public:
  inline explicit SentenceFeature(std::shared_ptr<NluContext> &nluContext);

 private:  
  std::shared_ptr<NluContext> nluContext_;
};

SentenceFeature::SentenceFeature(std::shared_ptr<NluContext> &nluContext) :
  nluContext_(nluContext) {}

}}}
