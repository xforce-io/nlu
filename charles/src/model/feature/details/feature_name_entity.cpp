#include "../feature_name_entity.h"

namespace xforce { namespace nlu { namespace charles {

FeatureNameEntity::FeatureNameEntity(
    ner::NameEntity &nameEntity, 
    size_t offset, 
    size_t len,
    size_t score) :
  nameEntity_(&nameEntity),
  offset_(offset),
  len_(len),
  score_(score) {}

}}}
