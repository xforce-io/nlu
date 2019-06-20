#include "../struct_pattern.h"

namespace xforce { namespace nlu { namespace milkie {

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
      if (nullptr != structPatternItem) {
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
    FATAL("invalid_pattern(" << statement << "]");
    return nullptr;
  }
}

}}}
