#include "../entry_adv.h"

namespace xforce { namespace nlu { namespace basic {

int EntryAdv::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  beforeSbv_ = !items[8].empty();
  return 0;
}

}}}

