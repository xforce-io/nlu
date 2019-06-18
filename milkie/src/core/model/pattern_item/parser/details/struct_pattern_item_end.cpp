#include "../struct_pattern_item_end.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternItemEnd> StructPatternItemEnd::Build(const std::wstring &statement) {
  return std::make_shared<StructPatternItemEnd>(
          "%",
          std::vector<std::wstring>());
}

}}}
