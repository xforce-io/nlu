#pragma once

#include "public.h"
#include "feature.h"

namespace xforce { namespace nlu { namespace charles {

class FeatureNameEntity : public Feature {
 public: 
  explicit FeatureNameEntity(
      std::shared_ptr<ner::NameEntity> &nameEntity, 
      size_t score);

  const ner::NameEntity& GetNameEntity() const { return *nameEntity_; }

 private: 
  std::shared_ptr<ner::NameEntity> nameEntity_;
  size_t score_;
};

}}}
