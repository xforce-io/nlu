#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Surname {
 private: 
  typedef std::unordered_map<wchar_t, std::wstring> Container; 
 
 public:
  Surname() {}

  bool Init(const std::string &dictpath);
  int StartWithSurname(const std::wstring &wstr, size_t offset) const;

 private:  
  Container container_;
};

}}}
