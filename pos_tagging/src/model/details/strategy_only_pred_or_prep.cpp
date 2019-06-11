#include "../strategy_only_pred_or_prep.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyOnlyPredOrPrep::Process(basic::NluContext &nluContext) {
  auto segments = nluContext.GetSegments().GetAll();
  auto theIter = segments.end();
  for (auto segIter = segments.begin(); segIter != segments.end(); ++segIter) {
    if (PosFilter_((*segIter)->GetPosTag())) {
      return;
    } else if ((*segIter)->SizePosTags() > 1) {
      for (auto &posTag : (*segIter)->GetPosTags()) {
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
    auto &posTags = (*theIter)->GetPosTags();
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
