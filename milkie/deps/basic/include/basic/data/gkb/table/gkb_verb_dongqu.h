#pragma once

#include "../../../public.h"
#include "../entry/entry_verb_dongqu.h"
#include "table.hpp"

namespace xforce { namespace nlu { namespace basic {

class GkbVerbDongqu : public Table<EntryVerbDongqu> {
 public:
  bool IsPhrase(
          const std::wstring &word0,
          const std::wstring &word1) const;
};

}}}
