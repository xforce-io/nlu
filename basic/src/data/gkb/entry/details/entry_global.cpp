#include "../entry_global.h"

namespace xforce { namespace nlu { namespace basic {

int EntryGlobal::Parse(const std::vector<std::wstring> &items) {
  word_ = items[0];
  posTag_ = PosTag::GetPosTag(items[1]);
  if (PosTag::Type::kUndef == posTag_) {
    return 1;
  }
  return 0;
}

}}}
