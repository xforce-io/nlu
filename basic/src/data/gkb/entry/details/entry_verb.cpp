#include "../entry_verb.h"

namespace xforce { namespace nlu { namespace basic {

int EntryVerb::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  if (L"体" == items[kColTiWeiZhun]) {
    tiWeiZhun_ = TiWeiZhun::kTi;
  } else if (L"谓" == items[kColTiWeiZhun]) {
    tiWeiZhun_ = TiWeiZhun::kWei;
  } else if (L"准" == items[kColTiWeiZhun]) {
    tiWeiZhun_ = TiWeiZhun::kZhun;
  } else {
    tiWeiZhun_ = TiWeiZhun::kNone;
  }

  dongjie_ = !items[kColDongjie].empty();
  dongqu_ = !items[kColDongqu].empty();
  return 0;
}

}}}
