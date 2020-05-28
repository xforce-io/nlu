#pragma once

#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

class Fragment;  

class FragmentInstruction {
 private:
  enum OpCategory {
    kAdd,
    kDel,
  };

 public:
  inline FragmentInstruction(
      OpCategory opCategory,
      Fragment::Category fragmentCategory);

  OpCategory GetOpCategory() const { return opCategory_; }
  Fragment::Category GetFragmentCategory() const { return fragmentCategory_; }
  void AddFragment(const std::shared_ptr<Fragment> &fragment);

 private:
  OpCategory opCategory_;
  Fragment::Category fragmentCategory_;
  std::vector<std::shared_ptr<Fragment>> fragments_;
};

FragmentInstruction::FragmentInstruction(
    OpCategory opCategory,
    Fragment::Category fragmentCategory) :
  opCategory_(opCategory),
  fragmentCategory_(fragmentCategory) {}

}}}
