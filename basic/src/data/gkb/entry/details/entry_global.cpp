#include "../entry_global.h"

namespace xforce { namespace nlu { namespace basic {

int EntryGlobal::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  posTag_ = PosTag::GetPosTagNaive(items[kColPos]);
  if (PosTag::Type::kUndef == posTag_) {
    return 1;
  }

  if (L"体" == items[kColTiWei]) {
    tiWei_ = TiWei::Val::kTi;
  } else if (L"谓" == items[kColTiWei]) {
    tiWei_ = TiWei::Val::kWei;
  } else {
    tiWei_ = TiWei::Val::kNone;
  }

  if (PosTag::Type::Val::kR == posTag_) {
    posTag_ = (TiWei::Val::kTi == tiWei_ ?
            PosTag::Type::Val::kRn :
            PosTag::Type::Val::kRp);
  }
  return 0;
}

}}}
