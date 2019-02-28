#pragma once

#include "../../public.h"
#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

class NonIntersectFragmentSet {
 private:
  struct Comparator {
    inline bool operator()(const std::shared_ptr<Fragment> &lhs, const std::shared_ptr<Fragment> &rhs);
  };

 public:
  inline bool Add(std::shared_ptr<Fragment> &fragment);
  inline void UnsafeAdd(std::shared_ptr<Fragment> &fragment);
  inline std::shared_ptr<NonIntersectFragmentSet> Copy() const;

  inline int GetScore() const;

 private:
  std::set<std::shared_ptr<Fragment>, Comparator> fragments_;
};

}}}

#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

bool NonIntersectFragmentSet::Comparator::operator()(
        const std::shared_ptr<Fragment> &lhs,
        const std::shared_ptr<Fragment> &rhs) {
  return lhs->GetOffset() >= rhs->GetOffset();
}

bool NonIntersectFragmentSet::Add(std::shared_ptr<Fragment> &newFragment) {
  for (auto &fragment : fragments_) {
    if (fragment->Intersect(*newFragment)) {
      return false;
    }
  }
  UnsafeAdd(newFragment);
  return true;
}

void NonIntersectFragmentSet::UnsafeAdd(std::shared_ptr<Fragment> &newFragment) {
  fragments_.insert(newFragment);
}

std::shared_ptr<NonIntersectFragmentSet> NonIntersectFragmentSet::Copy() const {
  auto copied = std::make_shared<NonIntersectFragmentSet>();
  copied->fragments_ = fragments_;
  return copied;
}

int  NonIntersectFragmentSet::GetScore() const {
  int score = 0;
  for (auto iter = fragments_.begin(); iter != fragments_.end(); ++iter) {
    score += (*iter)->GetConfidence().GetScore();
  }
  return score;
}

}}}
