#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryVerb : public Entry {
 public:
  const static size_t kColZhu = 7;
  const static size_t kColTiWeiZhun = 16;
  const static size_t kColDoubleArgs = 17;
  const static size_t kColDongjie = 19;
  const static size_t kColDongqu = 20;

 public:
  EntryVerb();

  int Parse(const std::vector<std::wstring> &items);

  bool IsZhu() const { return zhu_; }

  bool IsArgTi() const { return argTi_; }
  bool IsArgWei() const { return argWei_; }
  bool IsArgZhun() const { return argZhun_; }
  bool IsDoubleArgs() const { return doubleArgs_; }

  bool IsDongjie() const { return dongjie_; }
  bool IsDongqu() const { return dongqu_; }

 private:
  bool zhu_;

  bool argTi_;
  bool argWei_;
  bool argZhun_;
  bool doubleArgs_;

  bool dongjie_;
  bool dongqu_;
};

}}}
