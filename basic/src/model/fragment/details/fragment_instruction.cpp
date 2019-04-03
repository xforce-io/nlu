#include "../fragment_instruction.h"

namespace xforce { namespace nlu { namespace basic {

void FragmentInstruction::AddFragment(const std::shared_ptr<Fragment> &fragment) {
  fragments_.push_back(fragment);
}

}}}
