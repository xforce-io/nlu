#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureContent;
class SentenceFeatureSegment;

class Sentence {
 public: 
  inline explicit Sentence(std::shared_ptr<basic::NluContext> nluContext);
  inline explicit Sentence(const std::wstring &sentence);

  inline const std::wstring& GetSentence() const;
  inline std::wstring GetFeatureContent(ssize_t offset) const;
  inline std::shared_ptr<basic::Segments> GetFeatureSegmentsFromOffset(ssize_t offset) const;
  inline const basic::Segments* GetFeatureSegmentsAtOffset(ssize_t offset) const;
  const NluContext& GetNluContext() const { return *nluContext_; }

 protected: 
  std::shared_ptr<basic::NluContext> nluContext_;
  SentenceFeatureContent *featureContent_;
  SentenceFeatureSegment *featureSegment_;
};  

Sentence::Sentence(std::shared_ptr<basic::NluContext> nluContext) :
    nluContext_(nluContext) {
  featureContent_ = new SentenceFeatureContent(nluContext);
}

Sentence::Sentence(const std::wstring &sentence) :
  this(std::make_shared<basic::NluContext>(sentence)) {}

const std::wstring& Sentence::GetSentence() const {
  return nluContext_->GetText();
}

std::wstring Sentence::GetFeatureContent(ssize_t offset) const {
  return featureContent_->GetContent(offset);
}

std::shared_ptr<basic::Segments> Sentence::GetFeatureSegmentsFromOffset(ssize_t offset) const {
  if (NULL == featureSegment_) {
    featureSegment_ = new SentenceFeatureSegment(*nluContext_);
  }
  return featureSegment_->GetSegmentsFromOffset(offset);
}

const basic::Segments* Sentence::GetFeatureSegmentsAtOffset(ssize_t offset) const {
  if (NULL == featureSegment_) {
    featureSegment_ = new SentenceFeatureSegment(*nluContext_);
  }
  return featureSegment_->GetSegmentAtOffset(offset);
}

}}}
