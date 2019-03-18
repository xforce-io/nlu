#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureContent;
class SentenceFeatureSegment;

class Sentence {
 public: 
  inline explicit Sentence(std::shared_ptr<basic::NluContext> nluContext);
  inline explicit Sentence(const std::wstring &sentence);
  virtual ~Sentence();

  inline const std::wstring& GetSentence() const;
  inline std::wstring GetFeatureContent(ssize_t offset) const;
  inline std::shared_ptr<basic::Segment::Set> GetFeatureSegmentsFromOffset(ssize_t offset);
  inline const std::shared_ptr<basic::Segment> GetFeatureSegmentAtOffset(ssize_t offset);
  const basic::NluContext& GetNluContext() const { return *nluContext_; }
  std::shared_ptr<basic::NluContext> GetNluContext() { return nluContext_; }

 protected: 
  std::shared_ptr<basic::NluContext> nluContext_;
  SentenceFeatureContent *featureContent_;
  SentenceFeatureSegment *featureSegment_;
};

}}}

#include "sentence_feature_content.h"
#include "sentence_feature_segment.h"

namespace xforce { namespace nlu { namespace milkie {

Sentence::Sentence(std::shared_ptr<basic::NluContext> nluContext) :
    nluContext_(nluContext),
    featureSegment_(nullptr) {
  featureContent_ = new SentenceFeatureContent(nluContext);
}

Sentence::Sentence(const std::wstring &sentence) :
  Sentence(std::make_shared<basic::NluContext>(sentence)) {}

const std::wstring& Sentence::GetSentence() const {
  return nluContext_->GetQuery();
}

std::wstring Sentence::GetFeatureContent(ssize_t offset) const {
  return featureContent_->GetContent(offset);
}

std::shared_ptr<basic::Segment::Set> Sentence::GetFeatureSegmentsFromOffset(ssize_t offset) {
  if (nullptr == featureSegment_) {
    featureSegment_ = new SentenceFeatureSegment(nluContext_);
  }
  return featureSegment_->GetSegmentsFromOffset(offset);
}

const std::shared_ptr<basic::Segment> Sentence::GetFeatureSegmentAtOffset(ssize_t offset) {
  if (nullptr == featureSegment_) {
    featureSegment_ = new SentenceFeatureSegment(nluContext_);
  }
  return featureSegment_->GetSegmentAtOffset(offset);
}

}}}
