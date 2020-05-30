#include "../strategy_only_pred_or_prep.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyOnlyPredOrPrep::Process(basic::NluContext &nluContext) {
  Strategy::Process(nluContext);

  auto segments = nluContext.Get<basic::Segment>().GetAll();
  auto theIter = segments.end();
  for (auto segIter = segments.begin(); segIter != segments.end(); ++segIter) {
    if (PosFilter_((*segIter)->GetTag())) {
      return;
    } else if ((*segIter)->SizeTags() > 1) {
      for (auto &posTag : (*segIter)->GetTags()) {
        if (PosFilter_(posTag)) {
          if (theIter != segments.end()) {
            return;
          }
          theIter = segIter;
          break;
        }
      }
    }
  }

  if (theIter != segments.end()) {
    auto &posTags = (*theIter)->GetTags();
    auto iter = posTags.begin();
    while (iter != posTags.end()) {
      if (!PosFilter_(*iter)) {
        iter = posTags.erase(iter);
      } else {
        ++iter;
      }
    }
  }
}

}}}
