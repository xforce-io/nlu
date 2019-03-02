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
  inline size_t Size() const;

 protected:
  const std::wstring *text_;

  std::list<std::shared_ptr<Fragment>> fragments_;
};

size_t FragmentSet::Size() const {
  return fragments_.size();
}

}}}

