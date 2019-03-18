#pragma once

#include "../../../public.h"
#include "sentence_feature.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureSegment :public SentenceFeature {
 public:
  inline explicit SentenceFeatureSegment(std::shared_ptr<basic::NluContext> nluContext);

  inline std::shared_ptr<basic::Segment::Set> GetSegmentsFromOffset(ssize_t offset);
  inline const std::shared_ptr<basic::Segment> GetSegmentAtOffset(ssize_t offset) const;
};

SentenceFeatureSegment::SentenceFeatureSegment(std::shared_ptr<basic::NluContext> nluContext) :
    SentenceFeature(nluContext) {}

std::shared_ptr<basic::Segment::Set> SentenceFeatureSegment::GetSegmentsFromOffset(ssize_t offset) {
  std::shared_ptr<basic::Segment::Set> segments = std::make_shared<basic::Segment::Set>(nluContext_->GetQuery());

  size_t accuLen = 0;
  bool mark = false;
  for (auto &segment : nluContext_->GetSegments().GetAll()) {
    if (offset == (ssize_t)accuLen) {
      mark = true;
    }

    if (mark) {
      segments->Add(segment);
    }
    accuLen += segment->GetLen();
  }

  if (mark) {
    return segments;
  }
  return nullptr;
}

const std::shared_ptr<basic::Segment> SentenceFeatureSegment::GetSegmentAtOffset(ssize_t offset) const {
  ssize_t accuLen = 0;
  for (auto &segment : nluContext_->GetSegments().GetAll()) {
    if (offset == accuLen) {
      return segment;
    }
    accuLen += segment->GetLen();
  }
  return nullptr;
}

}}}
