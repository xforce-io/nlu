#pragma once

#include "fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
class FragmentSetNonMulti : public FragmentSet<FragmentType> {
 public:
  typedef FragmentSet<FragmentType> Super;

 private:
    struct Comparator {
        inline bool operator()(
                const std::shared_ptr<NonIntersectFragmentSet<FragmentType>> &lhs,
                const std::shared_ptr<NonIntersectFragmentSet<FragmentType>> &rhs);
    };

 public:
    explicit FragmentSetNonMulti(const std::wstring &text);

    void Add(std::shared_ptr<Fragment> fragment);
    void GenCandidates();

 private:
    std::list<std::shared_ptr<ConflictSet>> conflictSets_;
    std::set<std::shared_ptr<NonIntersectFragmentSet>, Comparator> candidates_;
};

}}}

#include "non_intersect_fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
bool FragmentSetNonMulti<FragmentType>::Comparator::operator()(
        const std::shared_ptr<NonIntersectFragmentSet> &lhs,
        const std::shared_ptr<NonIntersectFragmentSet> &rhs) {
  return lhs->GetScore() >= rhs->GetScore();
}

template <typename FragmentType>
FragmentSetNonMulti<FragmentType>::FragmentSetNonMulti(const std::wstring &text) :
        Super(text) {
  conflictSets_.resize(text.length());
}

template <typename FragmentType>
void FragmentSetNonMulti<FragmentType>::Add(std::shared_ptr<Fragment> fragment) {
  Super::Add(fragment);

  auto newConflictSet = std::make_shared<ConflictSet>();
  auto iter = conflictSets_.begin();
  while (iter != conflictSets_.end()) {
    newConflictSet->Merge(**iter);

    auto curIter = iter;
    conflictSets_.erase(curIter);
    ++iter;
  }
  conflictSets_.push_back(newConflictSet);
}

template <typename FragmentType>
void FragmentSetNonMulti<FragmentType>::GenCandidates() {
  auto toProcess = new std::list<std::shared_ptr<NonIntersectFragmentSet>>();
  auto result = new std::list<std::shared_ptr<NonIntersectFragmentSet>>();
  result->push_back(std::make_shared<NonIntersectFragmentSet>());
  for (auto &conflictSet : conflictSets_) {
    auto tmp = toProcess;
    toProcess = result;
    result = tmp;

    for (auto &nonIntersectFragmentSet : *toProcess) {
      conflictSet->Expand(*nonIntersectFragmentSet, *result);
    }
    toProcess->clear();
  }

  candidates_.clear();
  for (auto &nonIntersectFragmentSet : *result) {
    candidates_.insert(nonIntersectFragmentSet);
  }
}

}}}