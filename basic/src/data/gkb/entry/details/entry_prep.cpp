#include "../entry_prep.h"

namespace xforce { namespace nlu { namespace basic {

int EntryPrep::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  if (L"体" == items[kColTiWei]) {
    tiWei_ = TiWei::kTi;
  } else if (L"谓" == items[kColTiWei]) {
    tiWei_ = TiWei::kWei;
  } else if (L"兼" == items[kColTiWei]) {
    tiWei_ = TiWei::kJian;
  } else {
    tiWei_ = TiWei::kNone;
  }

  StrHelper::SplitStr(items[kColAfterWords], L',', afterWords_);

  for (size_t i=0; i < items[kColAfterPoses].length(); ++i) {
    auto posTag = PosTag::GetPosTag(items[kColAfterPoses][i]);
    if (PosTag::Type::kUndef != posTag) {
      afterPoses_.push_back(posTag);
    }
  }
  return 0;
}

}}}
