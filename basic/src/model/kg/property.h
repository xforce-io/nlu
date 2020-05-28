#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace basic {

class Property {
 public:
  inline explicit Property(const std::wstring &name);

  const std::wstring& Get() const { return name_; }

 private:
   std::wstring name_;
};

Property::Property(const std::wstring &name) :
    name_(name) {}

}}}