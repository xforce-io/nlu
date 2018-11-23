#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class FeatureSegments : public Feature {
 public: 
  inline void SetOffsets(const std::vector<size_t> &offsets);

 private:
  std::vector<std::shared_ptr<Segment>> segments_; 
};  

void FeatureSegment::SetOffsets(const std::vector<size_t> &offsets) {
  for () {
  }
}

}}}
