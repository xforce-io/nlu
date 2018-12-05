#include "../name_entity.h"

namespace xforce { namespace nlu { namespace ner {

void NameEntity::Dump(JsonType &jsonType) {
  jsonType["offset"] = offset_;
  jsonType["len"] = len_;
}

}}}
