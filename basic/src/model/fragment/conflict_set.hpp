#pragma once

#include "../../public.h"
#include "fragment.h"
#include "non_intersect_fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
class ConflictSet {
 public:
  ConflictSet();
  ConflictSet(const FragmentType &fragment);

  void Add(std::shared_ptr<FragmentType> fragment);
  void Merge(const ConflictSet &conflictSet);
  bool Intersect(const ConflictSet &conflictSet);
  bool Intersect(const FragmentType &fragment);
  void Expand(
          const NonIntersectFragmentSet<FragmentType> &nonIntersectFragmentSet,
          std::list<std::shared_ptr<NonIntersectFragmentSet<FragmentType>>> &results);

 private:
  void GenCombinations_(typename FragmentType::List &combinations);

 private:
  typename FragmentType::Vec fragments_;

  size_t begin_;
  size_t end_;
};

template <typename FragmentType>
ConflictSet<FragmentType>::ConflictSet() :
    begin_(std::numeric_limits<size_t>::max()),
    end_(std::numeric_limits<size_t >::min()) {}

template <typename FragmentType>
ConflictSet<FragmentType>::ConflictSet(const FragmentType &fragment) {
  begin_ = fragment.GetOffset();
  end_ = fragment.GetOffset() + fragment.GetLen();
}

template <typename FragmentType>
void ConflictSet<FragmentType>::Add(std::shared_ptr<FragmentType> fragment) {
  fragments_.push_back(fragment);
}

template <typename FragmentType>
void ConflictSet<FragmentType>::Merge(const ConflictSet<FragmentType> &other) {
  if (!Intersect(other)) {
    return;
  }

  for (auto &fragment : other.fragments_) {
    fragments_.push_back(fragment);
  }

  if (other.begin_ < begin_) {
    begin_ = other.begin_;
  }

  if (other.end_ > end_) {
    end_ = other.end_;
  }
}

template <typename FragmentType>
bool ConflictSet<FragmentType>::Intersect(const ConflictSet<FragmentType> &other) {
  for (auto &thisFragment : fragments_) {
    for (auto &thatFragment : other.fragments_) {
      if (thisFragment->Intersect(*thatFragment)) {
        return true;
      }
    }
  }
  return false;
}

template <typename FragmentType>
bool ConflictSet<FragmentType>::Intersect(const FragmentType &other) {
  for (auto &fragment : fragments_) {
    if (fragment->Intersect(other)) {
      return true;
    }
  }
  return false;
}

template <typename FragmentType>
void ConflictSet<FragmentType>::Expand(
        const NonIntersectFragmentSet<FragmentType> &nonIntersectFragmentSet,
        std::list<std::shared_ptr<NonIntersectFragmentSet<FragmentType>>> &results) {
  typename FragmentType::List combinations;
  GenCombinations_(combinations);
  for (auto &combination : combinations) {
    auto newSet = nonIntersectFragmentSet.Copy();
    for (auto &combElm : *combination) {
      newSet->UnsafeAdd(combElm);
    }
    results.push_back(newSet);
  }
}

template <typename FragmentType>
void ConflictSet<FragmentType>::GenCombinations_(typename FragmentType::List &combinations) {
  std::list<std::pair<std::shared_ptr<typename FragmentType::List>, int>> queue;
  queue.emplace_back(std::make_pair(std::make_shared<FragmentType::List>(), 0));
  while (!queue.empty()) {
    auto head = queue.front();
    queue.pop_front();

    bool hasConflict = false;
    auto &nextElement = fragments_[head.second];
    for (auto &each : *(head.first)) {
      if (each->Intersect(*nextElement)) {
        hasConflict = true;
        break;
      }
    }

    ++head.second;
    if (head.second >= fragments_.size()) {
      combinations.push_back(head.first);
    } else {
      queue.push_back(head);
    }

    if (hasConflict) {
      continue;
    }

    auto copiedFragmentList = std::make_shared<FragmentType::List>();
    *copiedFragmentList = *(head.first);
    copiedFragmentList->push_back(nextElement);
    queue.emplace_back(std::make_pair(copiedFragmentList, head.second));
  }
}

}}}
