#include "../entry_adv.h"

namespace xforce { namespace nlu { namespace basic {

int EntryAdv::Parse(const std::vector<std::wstring> &items) {
  word_ = items[0];
  beforeSbv_ = !items[8].empty();
  return 0;
}

}}}

