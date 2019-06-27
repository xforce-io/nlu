#include "../entry_verb_dongqu.h"

namespace xforce { namespace nlu { namespace basic {

int EntryVerbDongqu::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  if (!items[2].empty()) {
    connWords_.insert(L"来");
  }

  if (!items[3].empty()) {
    connWords_.insert(L"去");
  }

  if (!items[4].empty()) {
    connWords_.insert(L"上");
  }

  if (!items[5].empty()) {
    connWords_.insert(L"上来");
  }

  if (!items[6].empty()) {
    connWords_.insert(L"上去");
  }

  if (!items[7].empty()) {
    connWords_.insert(L"下");
  }

  if (!items[8].empty()) {
    connWords_.insert(L"下来");
  }

  if (!items[9].empty()) {
    connWords_.insert(L"下去");
  }

  if (!items[10].empty()) {
    connWords_.insert(L"进");
  }

  if (!items[11].empty()) {
    connWords_.insert(L"进来");
  }

  if (!items[12].empty()) {
    connWords_.insert(L"进去");
  }

  if (!items[13].empty()) {
    connWords_.insert(L"出");
  }

  if (!items[14].empty()) {
    connWords_.insert(L"出来");
  }

  if (!items[15].empty()) {
    connWords_.insert(L"出去");
  }

  if (!items[16].empty()) {
    connWords_.insert(L"回");
  }

  if (!items[17].empty()) {
    connWords_.insert(L"回来");
  }

  if (!items[18].empty()) {
    connWords_.insert(L"回去");
  }

  if (!items[19].empty()) {
    connWords_.insert(L"过");
  }

  if (!items[20].empty()) {
    connWords_.insert(L"过来");
  }

  if (!items[21].empty()) {
    connWords_.insert(L"过去");
  }

  if (!items[22].empty()) {
    connWords_.insert(L"起");
  }

  if (!items[23].empty()) {
    connWords_.insert(L"起来");
  }

  if (!items[24].empty()) {
    connWords_.insert(L"开");
  }

  if (!items[25].empty()) {
    connWords_.insert(L"开来");
  }

  if (!items[26].empty()) {
    connWords_.insert(L"到");
  }
  return 0;
}

bool EntryVerbDongqu::ConnWord(const std::wstring &word) const {
  return connWords_.find(word) != connWords_.end();
}

}}}
