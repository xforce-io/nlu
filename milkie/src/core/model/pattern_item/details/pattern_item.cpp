#include "../pattern_item.h"
#include "../parser/struct_pattern_item_str.h"
#include "../parser/struct_pattern_item_common.h"
#include "../parser/struct_pattern_item_end.h"
#include "../pattern_item_str.h"
#include "../pattern_item_reg.h"
#include "../pattern_item_wordpos.h"
#include "../pattern_item_syntax.h"
#include "../pattern_item_end.h"

namespace xforce { namespace nlu { namespace milkie {

const std::wstring* PatternItem::AsStr() const {
  if (typeid(*this) == typeid(PatternItemStr)) {
    return &(SCAST<const PatternItemStr*>(this)->GetPatternStr());
  }
  return nullptr;
}

std::shared_ptr<PatternItem> PatternItem::Build(const StructPatternItem &structPatternItem) {
  if (typeid(structPatternItem) == typeid(StructPatternItemStr)) {
    return std::make_shared<PatternItemStr>(SCAST<const StructPatternItemStr&>(structPatternItem).GetPatternStr());
  } else if (typeid(structPatternItem) == typeid(StructPatternItemCommon)) {
    const StructPatternItemCommon &structPatternItemCommon = SCAST<const StructPatternItemCommon &>(structPatternItem);
    if (structPatternItemCommon.GetCategory() == CategoryPatternItem::kReg) {
      return std::make_shared<PatternItemReg>(structPatternItemCommon.GetArgs(0));
    } else if (structPatternItemCommon.GetCategory() == CategoryPatternItem::kPos) {
      return std::make_shared<PatternItemWordpos>(structPatternItemCommon.GetArgs(0));
    } else if (structPatternItemCommon.GetCategory() == CategoryPatternItem::kChunk) {
      basic::SyntaxTag::Type::Val syntaxTag = basic::SyntaxTag::GetSyntaxTag(structPatternItemCommon.GetArgs(0));
      if (basic::SyntaxTag::Type::Val::kUndef != syntaxTag) {
        return std::make_shared<PatternItemSyntax>(syntaxTag);
      } else {
        FATAL("invalid_syntax_tag(" << structPatternItemCommon.GetArgs(0) << ")");
        return nullptr;
      }
    } else if (structPatternItemCommon.GetCategory() == CategoryPatternItem::kDep) {
      FATAL("[INTERNAL ERROR] dep_pattern_item_currently_not_supported");
      return nullptr;
    } else {
      FATAL("[INTERNAL ERROR] invalid_pattern_item_category("
                    << structPatternItemCommon.GetCategory()
                    << ")");
      return nullptr;
    }
  } else if (typeid(structPatternItem) == typeid(StructPatternItemEnd)) {
    return std::make_shared<PatternItemEnd>();
  } else {
    FATAL("[INTERNAL ERROR] invalid_pattern_item()");
    return nullptr;
  }
}

}}}
