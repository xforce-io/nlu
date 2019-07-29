#include "../entry.h"

namespace xforce { namespace nlu { namespace basic {

int Entry::Parse(const std::vector<std::wstring> &items) {
  word_ = items[0];
  return 0;
}

}}}
