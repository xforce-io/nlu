#pragma once

#include "public.h"
#include "feature.h"

namespace xforce { namespace nlu { namespace charles {

class Segment;  

class FeatureSegments : public Feature {
 public: 
  inline explicit FeatureSegments(const std::vector<size_t> &offsets); 
  inline std::vector<std::shared_ptr<Segment>>& GetSegments() { return segments_; }

 private:
  std::vector<std::shared_ptr<Segment>> segments_; 
};  

}}}

#include "../pos/segment.h"

namespace xforce { namespace nlu { namespace charles {

FeatureSegments::FeatureSegments(const std::vector<size_t> &offsets) {
  for (size_t i=0; i < offsets.size() - 1; ++i) {
    segments_.push_back(
        std::make_shared<Segment>(
          offsets[i], offsets[i+1] - offsets[i]));
  }
}

}}}
