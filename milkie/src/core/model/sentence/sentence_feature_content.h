#pragma once

#include "../../../public.h"
#include "sentence_feature.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureContent :public SentenceFeature {
 public: 
  inline explicit SentenceFeatureContent(std::shared_ptr<basic::NluContext> &nluContext);

  inline std::wstring GetContent(ssize_t offset);

 private: 
   std::wstring content_; 
};  

SentenceFeatureContent::SentenceFeatureContent(std::shared_ptr<basic::NluContext> &nluContext) :
    SentenceFeature(nluContext),
    content_(nluContext->GetQuery()) {}

std::wstring SentenceFeatureContent::GetContent(ssize_t offset) {
  return content_.substr(offset);
}

}}}
