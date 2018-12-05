#pragma once

#include "public.h"
#include "feature.h"

namespace xforce { namespace nlu { namespace charles {

class FeatureSegments;  
class Segment;

class FeatureNameEntity : public Feature {
 public: 
  explicit FeatureNameEntity(
      const FeatureSegments &featureSegments,
      std::shared_ptr<ner::NameEntity> &nameEntity, 
      size_t score);

  const ner::NameEntity& GetNameEntity() const { return *nameEntity_; }

  void Dump(JsonType &jsonType);

 private: 
  std::shared_ptr<ner::NameEntity> nameEntity_;
  basic::Segment segment_;
  size_t score_;
};

}}}
