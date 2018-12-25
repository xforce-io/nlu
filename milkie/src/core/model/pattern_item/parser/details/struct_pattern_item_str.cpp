#include "../struct_pattern_item_str.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<PatternItem> StructPatternItemStr::BuildPattern() {
  return std::make_shared<PatternItem>()
}

std::shared_ptr<StructPatternItemStr> StructPatternItemStr::Build(const std::string &statement) {
  ssize_t endStr = statement.find('"', 1);
  if (endStr>=0) {
    return new StructPatternItemStr(
        statement.substr(0, endStr+1),
        std::vector<String>(),
        statement.substr(1, endStr-1));
  }
  FATAL("invalid_pattern_item[" << statement << "]");
  return NULL;
}

}}}
