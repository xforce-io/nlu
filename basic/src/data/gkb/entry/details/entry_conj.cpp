#include "../entry_conj.h"

namespace xforce { namespace nlu { namespace basic {

EntryConj::EntryConj() :
    posPrev_(false),
    posMid_(false),
    posPost_(false) {}

int EntryConj::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  if (items[kColPos].find(L'前') != std::wstring::npos) {
    posPrev_ = true;
  }

  if (items[kColPos].find(L'中') != std::wstring::npos) {
    posMid_ = true;
  }

  if (items[kColPos].find(L'后') != std::wstring::npos) {
    posPost_ = true;
  }
  return 0;
}

}}}