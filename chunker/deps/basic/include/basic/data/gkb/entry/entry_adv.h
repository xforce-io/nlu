#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryAdv : public Entry {
 public:
  int Parse(const std::vector<std::wstring> &items);

  bool BeforeSbv() const { return beforeSbv_; }

 private:
  bool beforeSbv_;
};

}}}