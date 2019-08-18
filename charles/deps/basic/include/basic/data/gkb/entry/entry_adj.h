#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryAdj : public Entry {
 public:
  const static size_t kColDingyu = 7;

 public:
  int Parse(const std::vector<std::wstring> &items);

  bool Dingyu() const { return dingyu_; }

 private:
  bool dingyu_;
};

}}}