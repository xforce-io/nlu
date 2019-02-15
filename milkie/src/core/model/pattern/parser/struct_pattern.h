#pragma once

#include "../../../../public.h"
#include "../../struct_element.h"
#include "../../pattern/parser/struct_pattern.h"
#include "../../pattern_item/parser/struct_pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPattern :public StructElement {
 public:
  inline StructPattern(
      const std::wstring &statement,
      const StructPatternItem::Vector &structPatternItems);

  const StructPatternItem::Vector& GetPatternItems() const { return structPatternItems_; }

  static std::shared_ptr<StructPattern> Parse(const std::wstring &statement);

 private:    
  StructPatternItem::Vector structPatternItems_;
};

}}}

#include "../../pattern_item/parser/struct_pattern_item.h"
#include "../../pattern_item/pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

StructPattern::StructPattern(
    const std::wstring &statement,
    const StructPatternItem::Vector &structPatternItems) :
  StructElement(statement),
  structPatternItems_(structPatternItems) {}

}}}
