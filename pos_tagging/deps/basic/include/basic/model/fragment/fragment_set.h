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

 protected:
  const std::wstring *text_;

  std::list<std::shared_ptr<Fragment>> fragments_;
};

}}}

