#include "../struct_pattern_item.h"
#include "../struct_pattern_item_common.h"
#include "../struct_pattern_item_str.h"
#include "../struct_pattern_item_end.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternItem> StructPatternItem::Parse(const std::wstring &statement) {
  if (!statement.empty()) {
    if ('"' == statement[0]) {
      return StructPatternItemStr::Build(statement);
    } else if ('#' == statement[0]) {
      return StructPatternItemCommon::Build(statement);
    } else if ('%' == statement[0]) {
      return StructPatternItemEnd::Build(statement);
    } else {
      FATAL("invalid_leading_char_for_struct_pattern_item[" << statement << "]");
      return nullptr;
    }
  } else {
    FATAL("invalid_statement_for_struct_pattern_item[" << statement << "]");
    return nullptr;
  }
}

}}}
