#include "../public.h"

namespace xforce { namespace nlu { namespace milkie {

std::wstring Helper::PreprocessExprLine(const std::wstring &line) {
  std::wstring result;
  bool inStr = false;
  bool inFilter = false;
  for (size_t i=0; i < line.length(); ++i) {
    wchar_t curChar = line[i];
    if (L'"' == curChar) {
      inStr = !inStr;
    }

    if (L'|' == curChar) {
      inFilter = !inFilter;
    }

    if (inStr || inFilter || curChar != L' ') {
      result.append(1, curChar);
    }
  }
  return result;
}

}}}
