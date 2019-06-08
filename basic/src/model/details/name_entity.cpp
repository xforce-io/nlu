#include "../name_entity.h"

namespace xforce { namespace nlu { namespace basic {

const std::string& NameEntity::GetCategory() const {
  static const std::string kCategory = "nameEntity";
  return kCategory;
}

void NameEntity::Dump(JsonType &jsonType) {
  Super::Dump(jsonType);
}

NameEntity::~NameEntity() {}


}}}
