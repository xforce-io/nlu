#include "../struct_pattern_item_common.h"
#include "../../pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternItemCommon> StructPatternItemCommon::Build(const std::wstring &statement) {
  ssize_t endName = statement.find('(');
  if (endName>=0) {
    CategoryPatternItem::Category category = PatternItem::ParseCategory(statement.substr(1, endName-1));
    ssize_t bypassLeftBrackets = 0;
    ssize_t bypassRightBrackets = 0;
    ssize_t idx = endName+1;
    while (idx < (ssize_t)statement.length() && bypassLeftBrackets >= bypassRightBrackets) {
      if (statement[idx] == '(') {
        ++bypassLeftBrackets;
      } else if (statement[idx] == ')') {
        ++bypassRightBrackets;
      }
      ++idx;
    }

    if (bypassLeftBrackets >= bypassRightBrackets) {
      FATAL("invalid_pattern_item[" << statement << "]");
      return nullptr;
    }

    std::vector<std::wstring> args;
    std::wstring argsStr = StrHelper::Trim(statement.substr(endName+1, idx-endName-2));
    if (!argsStr.empty()) {
      if (category != CategoryPatternItem::kReg) {
        std::vector<std::wstring> argsItems;
        StrHelper::SplitStr(argsStr, L',', argsItems);
        for (auto argItem : argsItems) {
          args.push_back(argItem);
        }
      } else {
        args.push_back(argsStr);
      }
    }

    if (args.size() >= 1) {
      return std::make_shared<StructPatternItemCommon>(statement.substr(0, idx), args, category);
    }
  }
  FATAL("invalid_pattern_item[" << statement << "]");
  return nullptr;
}

}}}
