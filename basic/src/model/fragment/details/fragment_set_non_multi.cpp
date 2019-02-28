#include "../fragment_set_non_multi.h"
#include "../conflict_set.h"

namespace xforce { namespace nlu { namespace basic {

FragmentSetNonMulti::FragmentSetNonMulti(const std::wstring &text) :
        FragmentSet(text) {
  conflictSets_.resize(text.length());
}

void FragmentSetNonMulti::Add(std::shared_ptr<Fragment> fragment) {
  FragmentSet::Add(fragment);

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

void FragmentSetNonMulti::GenCandidates() {
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