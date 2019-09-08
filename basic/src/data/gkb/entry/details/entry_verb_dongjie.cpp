#include "../entry_verb_dongjie.h"

namespace xforce { namespace nlu { namespace basic {

int EntryVerbDongjie::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  if (!items[2].empty()) {
    connWords_.insert(L"了");
  }

  if (!items[3].empty()) {
    connWords_.insert(L"着");
  }

  if (!items[4].empty()) {
    connWords_.insert(L"成");
  }

  if (!items[5].empty()) {
    connWords_.insert(L"动");
  }

  if (!items[6].empty()) {
    connWords_.insert(L"好");
  }

  if (!items[7].empty()) {
    connWords_.insert(L"得了");
  }
  return 0;
}

bool EntryVerbDongjie::ConnWord(const std::wstring &word) const {
  return connWords_.find(word) != connWords_.end();
}

}}}
