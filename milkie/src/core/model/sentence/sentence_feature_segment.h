#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureSegment :public SentenceFeature {
 public:
  inline explicit SentenceFeatureSegment(std::shared_ptr<basic::NluContext> &nluContext);

  std::shared_ptr<basic::Segments> GetSegmentsFromOffset(ssize_t offset);
  const basic::Segment* GetSegmentAtOffset(ssize_t offset) const;
};

SentenceFeatureSegment::SentenceFeatureSegment(std::shared_ptr<NluContext> &nluContext) :
    SentenceFeature(nluContext) {}

std::shared_ptr<basic::Segments> SentenceFeatureSegment::GetSegmentsFromOffset(ssize_t offset) {
  std::shared_ptr<basic::Segments> segments = std::make_shared<basic::Segments>();

  size_t accuLen = 0;
  bool mark = false;
  for (auto &segment : *segments) {
    if (offset == accuLen) {
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
  return nullptr
}

}}}
