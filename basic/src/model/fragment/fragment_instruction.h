#pragma once

#include "fragment.h"
#include "fragment_category.h"

namespace xforce { namespace nlu { namespace basic {

class FragmentInstruction {
 private:
  enum OpCategory {
    kAdd,
    kDel,
  };

 public:
  inline FragmentInstruction(
      OpCategory opCategory,
      FragmentCategory::Category fragmentCategory);

  OpCategory GetOpCategory() const { return opCategory_; }
  FragmentCategory::Category GetFragmentCategory() const { return fragmentCategory_; }
  void AddFragment(const std::shared_ptr<Fragment> &fragment);

 private:
  OpCategory opCategory_;
  FragmentCategory::Category fragmentCategory_;
  std::vector<const std::shared_ptr<Fragment>> fragments_;
};

FragmentInstruction::FragmentInstruction(
    OpCategory opCategory,
    FragmentCategory::Category fragmentCategory) :
  opCategory_(opCategory),
  fragmentCategory_(fragmentCategory) {}

}}}
