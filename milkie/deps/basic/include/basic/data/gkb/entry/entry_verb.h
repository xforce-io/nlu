#pragma once

#include "../../../public.h"
#include "entry.h"

namespace xforce { namespace nlu { namespace basic {

class EntryVerb : public Entry {
 public:
  int Parse(const std::vector<std::wstring> &items);
};

}}}
