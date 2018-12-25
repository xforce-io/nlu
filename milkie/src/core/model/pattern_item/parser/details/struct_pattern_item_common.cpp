#include "../public.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<StructPatternItemCommon> StructPatternItemCommon::Build(const std::wstring &statement) {
  ssize_t endName = statement.find('(');
  if (endName>=0) {
    PatternItem::Category category = PatternItem::ParseCategory(statement.substr(1, statement.length() - 1));
    ssize_t bypassLeftBrackets = 0;
    ssize_t bypassRightBrackets = 0;
    ssize_t idx = endName+1;
    while (idx < statement.length() && bypassLeftBrackets >= bypassRightBrackets) {
      if (statement[idx] == '(') {
        ++bypassLeftBrackets;
      } else if (statement[idx] == ')') {
        ++bypassRightBrackets;
      }
      ++idx;
    }

    if (bypassLeftBrackets >= bypassRightBrackets) {
      FATAL("invalid_pattern_item[" << statement << "]");
      return NULL;
    }

    std::vector<std::wstring> args;
    std::wstring argsStr = StrHelper::Trim(statement.substr(endName+1, idx-endName-2));
    if (!argsStr.empty()) {
      std::vector<std::wstring> argsItems;
      StrHelper::SplitStr(argsStr, ',', argsItems);
      for (auto argItem : argsItems) {
        args.push_back(argItem);
      }
    }

    if (args.length() >= 1) {
      return new StructPatternItemCommon(statement, args, category);
    }
  }
  FATAL("invalid_pattern_item[" << statement << "]");
  return NULL;
}

}}}
