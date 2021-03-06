#include "../statistics_items.h"

namespace xforce { namespace nlu { namespace pos {

const int StatisticsItems::kThresholdCnt = 3;
const double StatisticsItems::kThresholdLeader = 0.95;

StatisticsItems::StatisticsItems() :
  count_(0) {}

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

const StatisticsUnit* StatisticsItems::GetDominator() {
  for (auto &statisticsUnit : statisticsItems_) {
    if (statisticsUnit.count * 1.0 / count_ >= kThresholdLeader &&
        statisticsUnit.count >= kThresholdCnt) {
      statisticsUnit.CalcConfidence(count_);
      return &statisticsUnit;
    }
  }
  return nullptr;
}

bool StatisticsItems::operator==(const StatisticsItems &other) const {
  if (GetCategory() != other.GetCategory() ||
      count_ != other.count_ ||
      statisticsItems_.size() != other.statisticsItems_.size()) {
    return false;
  }

  for (auto &unit : statisticsItems_) {
    bool ret = false;
    for (auto &otherUnit : other.statisticsItems_) {
      if (unit == otherUnit) {
        ret = true;
        break;
      }
    }

    if (!ret) {
      return false;
    }
  }
  return true;
}

StatisticsItems* StatisticsItems::Load(const std::string &str) {
  std::vector<std::string> items;
  StrHelper::SplitStr(str, kSep, items);

  size_t category;
  bool ret = StrHelper::GetNum(items[0], category);
  if (!ret) {
    FATAL("fail_get_statistics_items_category[" 
        << *StrHelper::Str2Wstr(items[0])
        << "]");
    return nullptr;
  }

  size_t count;
  ret = StrHelper::GetNum(items[1], count);
  if (!ret) {
    FATAL("fail_get_statistics_items_count[" 
        << *StrHelper::Str2Wstr(items[1])
        << "]");
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

  statisticsItems->count_ = count;

  for (size_t i=2; i < items.size(); ++i) {
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
  ss << GetCategory() << kSep << count_;
  for (auto &statisticsUnit : statisticsItems_) {
    ss << kSep;
    statisticsUnit.Dump(ss);
  }
}

}}}
