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

 private:  
  Container container_;
};

}}
