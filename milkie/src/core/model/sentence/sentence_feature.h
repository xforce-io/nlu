#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeature {
 public:
  inline explicit SentenceFeature(std::shared_ptr<basic::NluContext> &nluContext);

 protected:
  std::shared_ptr<basic::NluContext> nluContext_;
};

SentenceFeature::SentenceFeature(std::shared_ptr<basic::NluContext> &nluContext) :
  nluContext_(nluContext) {}

}}}
