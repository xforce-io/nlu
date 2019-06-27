#include "../entry_global.h"

namespace xforce { namespace nlu { namespace basic {

int EntryGlobal::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  posTag_ = PosTag::GetPosTag(items[1]);
  if (PosTag::Type::kUndef == posTag_) {
    return 1;
  }
  return 0;
}

}}}
