#include "../pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

const std::wstring* PatternItem::AsStr() {
  if (typeid(*this) == typeid(PatternItemStr)) {
    return &(SCAST<PatternItemStr*>(this)->GetPatternStr());
  }
  return nullptr;
}

std::shared_ptr<PatternItem> PatternItem::Build(const StructPatternItem &structPatternItem) {
  if (typeid(structPatternItem) == typeid(StructPatternItemStr)) {
    return std::make_shared<PatternItemStr>(SCAST<const StructPatternItemStr&>(structPatternItem).GetPatternStr());
  } else if (typeid(structPatternItem) == typeid(StructPatternItemCommon)) {
    const StructPatternItemCommon &structPatternItemCommon = SCAST<const StructPatternItemCommon&>(structPatternItem);
    if (structPatternItemCommon.GetCategory() == PatternItem::kPos) {
      return std::make_shared<>(structPatternItemCommon.GetArgs(0));
    } else if (structPatternItemCommon.GetCategory() == PatternItem::kDep) {
      FATAL("[INTERNAL ERROR] dep_pattern_item_currently_not_supported");
      return nullptr;
    } else {
      FATAL("[INTERNAL ERROR] invalid_pattern_item_category(" << 
          structPatternItemCommon.GetCategory() <<
          ")");
      return nullptr;
    }
  } else {
    FATAL("[INTERNAL ERROR] invalid_pattern_item()");
    return nullptr;
  }
}

}}}
