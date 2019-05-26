#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace basic {

class Entry {
 public:
  virtual ~Entry() {}

  const std::wstring &GetWord() const { return word_; }

  virtual bool Parse(const std::vector<std::wstring> &items) = 0;

 protected:
  std::wstring word_;
};

}}}
