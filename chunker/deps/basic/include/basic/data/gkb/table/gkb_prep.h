#pragma once

#include "../../../public.h"
#include "../entry/entry_prep.h"
#include "table.hpp"

namespace xforce { namespace nlu { namespace basic {

class GkbPrep : public Table<EntryPrep> {
 public:
  inline bool GetEntriesPrep(
          const std::wstring &word,
          std::vector<const EntryPrep*> &entriesPrep) const;
};

bool GkbPrep::GetEntriesPrep(
        const std::wstring &word,
        std::vector<const EntryPrep*> &entriesPrep) const {
  auto *entries = GetEntries(word);
  if (nullptr == entries) {
    return false;
  }

  for (size_t i=0; i < entries->size(); ++i) {
    entriesPrep.push_back(SCAST<const EntryPrep*>((*entries)[i]));
  }
  return true;
}

}}}
