#include "../struct_pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternItem> StructPatternItem::Build(const std::wstring &statement) {
  if (!statement.empty()) {
    if ('"' == statement[0]) {
      return StructPatternItemStr.Build(statement);
    } else if ('#' == statement[0]) {
      return StructPatternItemCommon.Build(statement);
    } else {
      FATAL("invalid_leading_char_for_struct_pattern_item[" << statement << "]");
      return NULL;
    }
  } else {
    FATAL("invalid_statement_for_struct_pattern_item[" << statement << "]");
    return NULL;
  }
}

}}}
