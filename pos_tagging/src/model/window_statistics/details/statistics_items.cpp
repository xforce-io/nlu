#include "../statistics_items.h"

namespace xforce { namespace nlu { namespace pos {

void StatisticsItems::Add(const StatisticsUnit &newItem) {
  count_ += newItem.count;
  for (auto &statisticsItem : statisticsItems_) {
    if (Match_(statisticsItem, newItem)) {
      statisticsItem.count += newItem.count;
      return;
    }
  }
  statisticsItems_.push_back(newItem);
}

}}}
