#include "../variable.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<std::wstring> Variable::GetVariableName(const std::wstring &statement, ssize_t startingIdx) {
  if (statement.length() - startingIdx <= 1) {
    FATAL("invalid_variable_name(" << StrHelper::Wstr2Str(statement) << "|" << startingIdx << ")");
    return nullptr;
  }

  ssize_t curIdx = startingIdx;
  while (curIdx < statement.length()) {
    if (!IsValidChar(statement[curIdx], curIdx-startingIdx)) {
      break;
    }
    ++curIdx;
  }

  if (curIdx>startingIdx) {
    return std::make_shared<std::wstring>(statement.substr(startingIdx, curIdx-startingIdx));
  } else {
    FATAL("invalid_variable_name(" << StrHelper::Wstr2Str(statement) << "|" << startingIdx << ")");
    return nullptr;
  }
}

}}}
