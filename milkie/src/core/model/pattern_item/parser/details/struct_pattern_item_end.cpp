#include "../struct_pattern_item_end.h"

namespace xforce { namespace nlu { namespace milkie {

StructPatternItemEnd::StructPatternItemEnd(
    const std::wstring &statement,
    const std::vector<std::wstring> &args) :
  StructPatternItem(statement, args) {}

std::shared_ptr<StructPatternItemEnd> StructPatternItemEnd::Build(const std::wstring &statement) {
  UNUSE(statement)
  return std::make_shared<StructPatternItemEnd>(
          L"%",
          std::vector<std::wstring>());
}

}}}
