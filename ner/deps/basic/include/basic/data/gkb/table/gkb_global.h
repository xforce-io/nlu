#pragma once

#include "../../../public.h"
#include "../entry/entry_global.h"
#include "table.hpp"

namespace xforce { namespace nlu { namespace basic {

class GkbGlobal : public Table<EntryGlobal> {
 public:
  inline std::shared_ptr<std::vector<PosTag::Type>> GetPosTags(const std::wstring &word) const;
};

std::shared_ptr<std::vector<PosTag::Type>> GkbGlobal::GetPosTags(const std::wstring &word) const {
  const std::vector<EntryGlobal*> *entries = GetEntries(word);
  if (nullptr == entries) {
    return nullptr;
  }

  auto result = std::make_shared<std::vector<PosTag::Type>>();
  for (auto *entry : *entries) {
    result->push_back(entry->GetPosTag());
  }
  return result;
}

}}}
