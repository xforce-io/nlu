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

  inline static std::shared_ptr<StructPattern> Parse(const std::wstring &statement);

 private:    
  const StructPatternItem::Vector &structPatternItems_;
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

std::shared_ptr<StructPattern> StructPattern::Parse(const std::wstring &statement) {
  std::vector<std::shared_ptr<StructPatternItem>> structPatternItems;
  ssize_t curIdx = 0;
  bool exit = false;
  bool lastCharConnector = true;
  while (!exit && curIdx < (ssize_t)statement.length()) {
    if (' ' == statement[curIdx]) {
      ++curIdx;
    } else if ('&' == statement[curIdx] &&
        curIdx < (ssize_t)(statement.length() - 1) &&
        '&' == statement[curIdx+1]) {
      lastCharConnector = true;
      curIdx += 2;
    } else if (PatternItem::IsStartingChar(statement[curIdx]) && lastCharConnector) {
      lastCharConnector = false;
      auto structPatternItem = StructPatternItem::Parse(statement.substr(curIdx));
      if (structPatternItem.get() != nullptr) {
        structPatternItems.push_back(structPatternItem);
        curIdx += structPatternItem->GetStatement().length();
      } else {
        exit = true;
      }
    } else {
      exit = true;
    }
  }

  if (!structPatternItems.empty()) {
    return std::make_shared<StructPattern>(statement.substr(0, curIdx), structPatternItems);
  } else {
    FATAL("invalid_pattern(" << StrHelper::Wstr2Str(statement) << "]");
    return nullptr;
  }
}

}}}
