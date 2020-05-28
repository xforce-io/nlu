#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryAdj : public Entry {
 public:
  const static size_t kColDingyu = 7;
  const static size_t kColZhuangyu = 12;

 public:
  int Parse(const std::vector<std::wstring> &items);

  bool Dingyu() const { return dingyu_; }
  bool Zhuangyu() const { return zhuangyu_; }

 private:
  bool dingyu_;
  bool zhuangyu_;
};

}}}