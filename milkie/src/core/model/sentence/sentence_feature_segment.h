#pragma once

#include "../../../public.h"
#include "sentence_feature.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureSegment :public SentenceFeature {
 public:
  inline explicit SentenceFeatureSegment(std::shared_ptr<basic::NluContext> nluContext);

  inline std::shared_ptr<basic::Segment::Vector> GetSegmentsFromOffset(ssize_t offset);
  inline const basic::Segment* GetSegmentAtOffset(ssize_t offset) const;
};

SentenceFeatureSegment::SentenceFeatureSegment(std::shared_ptr<basic::NluContext> nluContext) :
    SentenceFeature(nluContext) {}

std::shared_ptr<basic::Segment::Vector> SentenceFeatureSegment::GetSegmentsFromOffset(ssize_t offset) {
  std::shared_ptr<basic::Segment::Vector> segments = std::make_shared<basic::Segment::Vector>();

  size_t accuLen = 0;
  bool mark = false;
  for (auto &segment : nluContext_->GetSegments()) {
    if (offset == (ssize_t)accuLen) {
      mark = true;
    }

    if (mark) {
      segments->push_back(segment);
    }
    accuLen += segment.GetLen();
  }

  if (mark) {
    return segments;
  }
  return nullptr;
}

const basic::Segment* SentenceFeatureSegment::GetSegmentAtOffset(ssize_t offset) const {
  ssize_t accuLen = 0;
  for (auto &segment : nluContext_->GetSegments()) {
    if (offset == accuLen) {
      return &segment;
    }
    accuLen += segment.GetLen();
  }
  return nullptr;
}

}}}
