#pragma once

#include "../../public.h"
#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

class NonIntersectFragmentSet;

class ConflictSet {
 public:
  ConflictSet();
  ConflictSet(const Fragment &fragment);

  void Add(std::shared_ptr<Fragment> fragment);
  void Merge(const ConflictSet &conflictSet);
  bool Intersect(const ConflictSet &conflictSet);
  bool Intersect(const Fragment &fragment);
  void Expand(
          const NonIntersectFragmentSet &nonIntersectFragmentSet,
          std::list<std::shared_ptr<NonIntersectFragmentSet>> &results);

 private:
  void GenCombinations_(std::list<std::shared_ptr<FragmentList>> &combinations);

 private:
  FragmentVec fragments_;

  size_t begin_;
  size_t end_;
};

}}}
