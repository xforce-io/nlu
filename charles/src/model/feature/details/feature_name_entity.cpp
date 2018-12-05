#include "../feature_name_entity.h"
#include "../feature_segments.h"

namespace xforce { namespace nlu { namespace charles {

FeatureNameEntity::FeatureNameEntity(
    const FeatureSegments &featureSegments,
    std::shared_ptr<ner::NameEntity> &nameEntity, 
    size_t score) :
      nameEntity_(nameEntity),
      score_(score) {
  bool matched = false;
  for (auto &segment : featureSegments.GetSegments()) {
    if (segment.GetOffset() == nameEntity->GetOffset() &&
        segment.GetLen() == nameEntity->GetLen()) {
      segment_ = segment;
      segment_.SetPos(basic::Pos::kN);
      matched = true;
    }
  }  

  if (!matched) {
    ERROR("invalid_name_entity[" 
        << nameEntity->GetOffset() 
        << "|" 
        << nameEntity->GetLen() 
        << "]");
  }
}

void FeatureNameEntity::Dump(JsonType &jsonType) {
  jsonType["score"] = (int64_t)score_;
  nameEntity_->Dump(jsonType["nameEntity"]);
}

}}}
