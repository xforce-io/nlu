#include "../statistics_items.h"

namespace xforce { namespace nlu { namespace pos {

const int StatisticsItems::kThresholdCnt = 3;
const double StatisticsItems::kThresholdLeader = 0.95;

void StatisticsItems::Add(const StatisticsUnit &newItem) {
  count_ += newItem.count;

  if (!IsValid_(newItem)) {
    return;
  }

  for (auto &statisticsItem : statisticsItems_) {
    if (Match_(statisticsItem, newItem)) {
      statisticsItem.count += newItem.count;
      return;
    }
  }
  statisticsItems_.push_back(newItem);
}

const StatisticsUnit* StatisticsItems::GetDominator() const {
  for (auto &statisticsUnit : statisticsItems_) {
    if (statisticsUnit.count * 1.0 / count_ >= kThresholdLeader &&
        statisticsUnit.count >= kThresholdCnt) {
      return &statisticsUnit;
    }
  }
  return nullptr;
}

}}}
