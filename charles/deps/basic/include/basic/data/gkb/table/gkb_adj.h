#pragma once

#include "../../../public.h"
#include "../entry/entry_adj.h"
#include "table.hpp"

namespace xforce { namespace nlu { namespace basic {

class GkbAdj : public Table<EntryAdj> {
 public:
  inline int Dingyu(const std::wstring &word) const;
};

int GkbAdj::Dingyu(const std::wstring &word) const {
  auto *entries = GetEntries(word);
  if (nullptr == entries) {
    return -1;
  }

  for (auto *entry : *entries) {
    if (entry->Dingyu()) {
      return 0;
    }
  }
  return 1;
}

}}}
