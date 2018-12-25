#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureContent :public SentenceFeature {
 public: 
  inline explicit SentenceFeatureContent(std::shared_ptr<NluContext> &nluContext);

  inline std::wstring GetContent(ssize_t offset);

 private: 
   std::wstring content_; 
};  

SentenceFeatureContent::SentenceFeatureContent(std::shared_ptr<NluContext> &nluContext) :
    SentenceFeature(nluContext),
    content_(nluContext.GetText()) {}

std::wstring SentenceFeatureContent::GetContent(ssize_t offset) {
  return content_.substr(offset);
}

}}}
