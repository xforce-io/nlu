#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryVerbDongjie : public Entry {
 public:
  int Parse(const std::vector<std::wstring> &items);
  bool ConnWord(const std::wstring &word) const;

 private:
  std::unordered_set<std::wstring> connWords_;
};

}}}
