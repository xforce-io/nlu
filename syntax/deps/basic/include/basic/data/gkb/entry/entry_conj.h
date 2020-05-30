#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryConj : public Entry {
 public:
  const static size_t kColPos = 6;

 public:
  EntryConj();

  int Parse(const std::vector<std::wstring> &items);

  bool posPrev() const { return posPrev_; }
  bool posMid() const { return posMid_; }
  bool posPost() const { return posPost_; }

 private:
  bool posPrev_;
  bool posMid_;
  bool posPost_;
};

}}}