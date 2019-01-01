#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Variable {
 public: 
  inline static bool IsStartingChar(wchar_t c);
  inline static std::shared_ptr<std::wstring> GetVariableName(const std::wstring &statement);
  static std::shared_ptr<std::wstring> GetVariableName(const std::wstring &statement, ssize_t startingIdx);
  inline static bool IsVariableName(const std::wstring &statement);
  inline static bool IsValidChar(wchar_t c, ssize_t idx);

 private:
};  

bool Variable::IsStartingChar(wchar_t c) {
  return L'$' == c;
}

std::shared_ptr<std::wstring> Variable::GetVariableName(const std::wstring &statement) {
  return GetVariableName(statement, 0);
}

bool Variable::IsVariableName(const std::wstring &statement) {
  for (size_t idx=0; idx < statement.length(); ++idx) {
    wchar_t c = statement[idx];
    if (!IsValidChar(c, idx)) {
      return false;
    }

    if (L'*' == c && idx != 0) {
      return false;
    }
  }
  return true;
}

bool Variable::IsValidChar(wchar_t c, ssize_t idx) {
  return (c >= L'a' && c <= L'z') ||
    (c >= L'A' && c <= L'Z') ||
    (c >= L'0' && c <= L'9') ||
    (c >= L'*' && 0==idx) ||
    L'_' == c;
}

}}}
