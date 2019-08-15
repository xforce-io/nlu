#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryVerb : public Entry {
 public:
  const static size_t kColTiWeiZhun = 16;
  const static size_t kColDongjie = 19;
  const static size_t kColDongqu = 20;

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
  bool isDongjie() const { return dongjie_; }
  bool isDongqu() const { return dongqu_; }

 private:
  TiWeiZhun::Val tiWeiZhun_;
  bool dongjie_;
  bool dongqu_;
};

}}}
