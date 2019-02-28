#pragma once

#include "fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

class FragmentSetNonMulti : public FragmentSet {
 private:
    struct Comparator {
        inline bool operator()(
                const std::shared_ptr<NonIntersectFragmentSet> &lhs,
                const std::shared_ptr<NonIntersectFragmentSet> &rhs);
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

#include "non_intersect_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

bool FragmentSetNonMulti::Comparator::operator()(
        const std::shared_ptr<NonIntersectFragmentSet> &lhs,
        const std::shared_ptr<NonIntersectFragmentSet> &rhs) {
  return lhs->GetScore() >= rhs->GetScore();
}

}}}