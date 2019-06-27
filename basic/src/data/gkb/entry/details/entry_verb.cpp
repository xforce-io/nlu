#include "../entry_verb.h"

namespace xforce { namespace nlu { namespace basic {

int EntryVerb::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  return 0;
}

}}}
