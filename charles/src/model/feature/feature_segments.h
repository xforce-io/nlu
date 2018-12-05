#pragma once

#include "public.h"
#include "feature.h"

namespace xforce { namespace nlu { namespace charles {

class Segment;  

class FeatureSegments : public Feature {
 public: 
  inline explicit FeatureSegments(
      const std::wstring &clause,
      basic::Segments &segments); 

  inline const basic::Segments& GetSegments() const { return segments_; }

  void Dump(JsonType &jsonType);

 private:
  const std::wstring &clause_;
  basic::Segments segments_; 
};  

}}}

namespace xforce { namespace nlu { namespace charles {

FeatureSegments::FeatureSegments(
    const std::wstring &clause,
    basic::Segments &segments) :
      clause_(clause) {
  pos::PosTagging::Tagging(clause, segments);
  segments_ = segments;
}

}}}
