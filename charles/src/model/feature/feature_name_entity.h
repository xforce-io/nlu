#pragma once

#include "public.h"
#include "feature.h"

namespace xforce { namespace nlu { namespace charles {

class FeatureNameEntity : public Feature {
 public: 
  explicit FeatureNameEntity(
      ner::NameEntity &nameEntity, 
      size_t offset, 
      size_t len,
      size_t score);

  const ner::NameEntity& GetNameEntity() const { return *nameEntity_; }
  ner::NameEntity& GetNameEntity() { return *nameEntity_; }

 private: 
  ner::NameEntity* nameEntity_;
};

}}}
