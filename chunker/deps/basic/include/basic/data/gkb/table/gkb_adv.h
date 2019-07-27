#pragma once

#include "../../../public.h"
#include "../entry/entry_adv.h"
#include "table.hpp"

namespace xforce { namespace nlu { namespace basic {

class GkbAdv : public Table<EntryAdv> {
 public:
  inline int beforeSbv(const std::wstring &word) const;
};

int GkbAdv::beforeSbv(const std::wstring &word) const {
  auto *entries = GetEntries(word);
  if (nullptr == entries) {
    return -1;
  }

  for (auto *entry : *entries) {
    if (entry->BeforeSbv()) {
      return 0;
    }
  }
  return 1;
}

}}}
