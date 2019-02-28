#pragma once

#include "fragment_set_non_multi.h"

namespace xforce { namespace nlu { namespace basic {

class FragmentSetTree : public FragmentSetNonMulti {
 public:
  explicit FragmentSetTree(const std::wstring &text);
};

}}}
