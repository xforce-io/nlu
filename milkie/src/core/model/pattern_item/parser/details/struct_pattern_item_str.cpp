#include "../struct_pattern_item_str.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternItemStr> StructPatternItemStr::Build(const std::wstring &statement) {
  ssize_t endStr = statement.find('"', 1);
  if (endStr>=0) {
    return std::make_shared<StructPatternItemStr>(
        statement.substr(0, endStr+1),
        std::vector<std::wstring>(),
        statement.substr(1, endStr-1));
  }
  FATAL("invalid_pattern_item[" << statement << "]");
  return nullptr;
}

}}}
