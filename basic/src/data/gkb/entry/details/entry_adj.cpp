#include "../entry_adj.h"

namespace xforce { namespace nlu { namespace basic {

int EntryAdj::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  dingyu_ = !items[kColDingyu].empty();
  zhuangyu_ = !items[kColZhuangyu].empty();
  return 0;
}

}}}

