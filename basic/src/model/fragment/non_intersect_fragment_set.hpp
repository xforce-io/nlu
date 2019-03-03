#pragma once

#include "../../public.h"
#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
class NonIntersectFragmentSet {
 private:
  struct Comparator {
    inline bool operator()(const std::shared_ptr<FragmentType> &lhs, const std::shared_ptr<FragmentType> &rhs);
  };

 public:
  inline bool Add(std::shared_ptr<FragmentType> &fragment);
  inline void UnsafeAdd(std::shared_ptr<FragmentType> &fragment);
  inline std::shared_ptr<NonIntersectFragmentSet<FragmentType>> Copy() const;

  inline int GetScore() const;

 private:
  std::set<std::shared_ptr<FragmentType>, Comparator> fragments_;
};

}}}

#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
bool NonIntersectFragmentSet<FragmentType>::Comparator::operator()(
        const std::shared_ptr<FragmentType> &lhs,
        const std::shared_ptr<FragmentType> &rhs) {
  return lhs->GetOffset() >= rhs->GetOffset();
}

template <typename FragmentType>
bool NonIntersectFragmentSet<FragmentType>::Add(std::shared_ptr<FragmentType> &newFragment) {
  for (auto &fragment : fragments_) {
    if (fragment->Intersect(*newFragment)) {
      return false;
    }
  }
  UnsafeAdd(newFragment);
  return true;
}

template <typename FragmentType>
void NonIntersectFragmentSet<FragmentType>::UnsafeAdd(std::shared_ptr<FragmentType> &newFragment) {
  fragments_.insert(newFragment);
}

template <typename FragmentType>
std::shared_ptr<NonIntersectFragmentSet<FragmentType>> NonIntersectFragmentSet<FragmentType>::Copy() const {
  auto copied = std::make_shared<NonIntersectFragmentSet<FragmentType>>();
  copied->fragments_ = fragments_;
  return copied;
}

template <typename FragmentType>
int NonIntersectFragmentSet<FragmentType>::GetScore() const {
  int score = 0;
  for (auto iter = fragments_.begin(); iter != fragments_.end(); ++iter) {
    score += (*iter)->GetConfidence().GetScore();
  }
  return score;
}

}}}
