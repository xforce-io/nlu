#include "../feature_name_entity.h"

namespace xforce { namespace nlu { namespace charles {

FeatureNameEntity::FeatureNameEntity(
    std::shared_ptr<ner::NameEntity> &nameEntity, 
    size_t score) :
  nameEntity_(nameEntity),
  score_(score) {}

}}}
