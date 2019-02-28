#include "../conflict_set.h"
#include "../fragment.h"
#include "../non_intersect_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

ConflictSet::ConflictSet() :
    begin_(std::numeric_limits<size_t>::max()),
    end_(std::numeric_limits<size_t >::min()) {}

ConflictSet::ConflictSet(const Fragment &fragment) {
  begin_ = fragment.GetOffset();
  end_ = fragment.GetOffset() + fragment.GetLen();
}

void ConflictSet::Add(std::shared_ptr<Fragment> fragment) {
  fragments_.push_back(fragment);
}

void ConflictSet::Merge(const ConflictSet &other) {
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

bool ConflictSet::Intersect(const ConflictSet &other) {
  for (auto &thisFragment : fragments_) {
    for (auto &thatFragment : other.fragments_) {
      if (thisFragment->Intersect(*thatFragment)) {
        return true;
      }
    }
  }
  return false;
}

bool ConflictSet::Intersect(const Fragment &other) {
  for (auto &fragment : fragments_) {
    if (fragment->Intersect(other)) {
      return true;
    }
  }
  return false;
}

void ConflictSet::Expand(
        const NonIntersectFragmentSet &nonIntersectFragmentSet,
        std::list<std::shared_ptr<NonIntersectFragmentSet>> &results) {
  std::list<std::shared_ptr<FragmentList>> combinations;
  GenCombinations_(combinations);
  for (auto &combination : combinations) {
    auto newSet = nonIntersectFragmentSet.Copy();
    for (auto &combElm : *combination) {
      newSet->UnsafeAdd(combElm);
    }
    results.push_back(newSet);
  }
}

void ConflictSet::GenCombinations_(std::list<std::shared_ptr<FragmentList>> &combinations) {
  std::list<std::pair<std::shared_ptr<FragmentList>, int>> queue;
  queue.emplace_back(std::make_pair(std::make_shared<FragmentList>(), 0));
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

    auto copiedFragmentList = std::make_shared<FragmentList>();
    *copiedFragmentList = *(head.first);
    copiedFragmentList->push_back(nextElement);
    queue.emplace_back(std::make_pair(copiedFragmentList, head.second));
  }
}

}}}
