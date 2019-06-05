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

StatisticsItems* StatisticsItems::Load(const std::string &str) {
  std::vector<std::string> items;
  StrHelper::SplitStr(str, kSep, items);

  size_t category;
  bool ret = StrHelper::GetNum(items[0], category);
  if (!ret) {
    FATAL("fail_get_statistics_items_category[" << items[0] << "]");
    return nullptr;
  }

  StatisticsItems *statisticsItems;
  switch (category) {
    case StatisticsItems::kCategory0 :
      statisticsItems = new StatisticsItems0();
      break;
    case StatisticsItems::kCategory1 :
      statisticsItems = new StatisticsItems1();
      break;
    case StatisticsItems::kCategory2 :
      statisticsItems = new StatisticsItems2();
      break;
    case StatisticsItems::kCategory01 :
      statisticsItems = new StatisticsItems01();
      break;
    case StatisticsItems::kCategory02 :
      statisticsItems = new StatisticsItems02();
      break;
    case StatisticsItems::kCategory12 :
      statisticsItems = new StatisticsItems12();
      break;
    case StatisticsItems::kCategory012 :
      statisticsItems = new StatisticsItems012();
      break;
    default:
      return nullptr;
  }

  for (size_t i=1; i < items.size(); ++i) {
    StatisticsUnit statisticsUnit;
    int ret1 = statisticsUnit.Load(items[i]);
    if (0==ret1) {
      statisticsItems->statisticsItems_.push_back(statisticsUnit);
    } else {
      return nullptr;
    }
  }
  return statisticsItems;
}

void StatisticsItems::Dump(std::stringstream &ss) const {
  ss << GetCategory();
  for (auto &statisticsUnit : statisticsItems_) {
    ss << kSep;
    statisticsUnit.Dump(ss);
  }
}

}}}
