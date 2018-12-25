#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class StructElement {
 public: 
  inline explicit StructElement(const std::wstring &statement);

  const std::wstring& GetStatement() const { return statement_; }

 private:  
  std::wstring statement_;
};

StructElement::StructElement(const std::wstring &statement) :
    statement_(statement) {}

}}}
