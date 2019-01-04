#pragma once

#include "../public.h"
#include "../../struct_element.h"
#include "struct_pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItem;

class StructPatternItemCommon : public StructPatternItem {
 public: 
  inline StructPatternItemCommon(
      const std::wstring &statement, 
      const std::vector<std::wstring> &args,
      CategoryPatternItem::Category category);

  std::shared_ptr<PatternItem> BuildPattern();

  CategoryPatternItem::Category GetCategory() const { return category_; }

  static std::shared_ptr<StructPatternItemCommon> Build(const std::wstring &statement);
 
 private: 
  CategoryPatternItem::Category category_;
};

StructPatternItemCommon::StructPatternItemCommon(
    const std::wstring &statement, 
    const Wstrings &args,
    CategoryPatternItem::Category category) :
  StructPatternItem(statement, args),
  category_(category) {}

}}}
