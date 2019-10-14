#pragma once

#include "../../../public.h"
#include "../entry/entry_global.h"
#include "table.hpp"

namespace xforce { namespace nlu { namespace basic {

class GkbGlobal : public Table<EntryGlobal> {
 public:
  std::shared_ptr<std::vector<PosTag::Type::Val>> GetPosTags(const std::wstring &word) const;
};



}}}
