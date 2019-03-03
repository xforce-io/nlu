#pragma once

#include "../../public.h"
#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

class ConflictSet;
class NonIntersectFragmentSet;

class FragmentSet {
 public:
  explicit FragmentSet(const std::wstring &text);

  virtual void Add(std::shared_ptr<Fragment> fragment);
  void Add(const Fragment &fragment);
  inline const std::shared_ptr<Fragment>& operator[](size_t i) const;
  inline std::shared_ptr<Fragment>& operator[](size_t i);
  inline size_t Size() const;

 protected:
  const std::wstring *text_;

  std::vector<std::shared_ptr<Fragment>> fragments_;
};

const std::shared_ptr<Fragment>& FragmentSet::operator[](size_t i) const {
  return fragments_[i];
}

std::shared_ptr<Fragment>& FragmentSet::operator[](size_t i) {
  return fragments_[i];
}

size_t FragmentSet::Size() const {
  return fragments_.size();
}

}}}

