#include "../fragment_set.h"
#include "../conflict_set.h"

namespace xforce { namespace nlu { namespace basic {

FragmentSet::FragmentSet(const std::wstring &text) :
    text_(&text) {}

void FragmentSet::Add(std::shared_ptr<Fragment> fragment) {
  fragments_.push_back(fragment);
}

}}}
