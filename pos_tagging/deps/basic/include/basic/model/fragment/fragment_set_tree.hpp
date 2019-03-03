#pragma once

#include "fragment_set_non_multi.hpp"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
class FragmentSetTree : public FragmentSetNonMulti<FragmentType> {
};

}}}
