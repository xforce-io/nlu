#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryVerb : public Entry {
 public:
  const static size_t kColTiWeiZhun = 16;

  struct TiWeiZhun {
    enum Val {
      kNone,
      kTi,
      kWei,
      kZhun,
      kOther,
    };
  };

 public:
  int Parse(const std::vector<std::wstring> &items);

  TiWeiZhun::Val TiWeiZhun() const { return tiWeiZhun_; }

 private:
  TiWeiZhun::Val tiWeiZhun_;
};

}}}
