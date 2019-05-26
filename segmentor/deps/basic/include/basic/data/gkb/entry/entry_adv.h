#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryAdv : public Entry {
 public:
  bool Parse(const std::vector<std::wstring> &items);

  bool beforeSbv() const { return beforeSbv_; }

 private:
  bool beforeSbv_;
};

}}}