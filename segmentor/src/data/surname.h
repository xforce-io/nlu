#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Surname {
 private: 
  typedef std::tr1::unordered_map<wchar_t, std::wstring> Container; 
 
 public:
  Surname() {}

  bool Init(const std::string &dictpath);
  int StartWithSurname(const std::wstring &wstr, size_t offset);
  inline int StartWithSurname(const std::string &str, size_t offset);

 private:  
  Container container_;
};

int StartWithSurname(const std::string &str, size_t offset) {
  std::wstring wstr;
  if (!StrHelper::Str2Wstr(str.substr(offset), wstr)) {
    return -1;
  }
  return StartWithSurname(wstr);
}

}}
