#include "../feature_segments.h"

namespace xforce { namespace nlu { namespace charles {

void FeatureSegments::Dump(JsonType &jsonType) {
  for (size_t i=0; i < segments_.size(); ++i) {
    segments_[i].Dump(jsonType[i]);
  }
}

}}}
