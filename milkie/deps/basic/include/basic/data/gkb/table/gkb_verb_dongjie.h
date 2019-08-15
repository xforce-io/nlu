#pragma once

#include "../../../public.h"
#include "../entry/entry_verb_dongjie.h"
#include "table.hpp"

namespace xforce { namespace nlu { namespace basic {

class GkbVerbDongjie : public Table<EntryVerbDongjie> {
 public:
  bool IsPhrase(
          const std::wstring &word0,
          const std::wstring &word1) const;
};

}}}
