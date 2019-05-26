#include "../entry_global.h"

namespace xforce { namespace nlu { namespace basic {

bool EntryGlobal::Parse(const std::vector<std::wstring> &items) {
  word_ = items[0];
  posTag_ = PosTag::GetPosTag(items[1]);
  return true;
}

}}}
