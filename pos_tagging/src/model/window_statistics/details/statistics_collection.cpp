#include "../statistics_collection.h"

namespace xforce { namespace nlu { namespace pos {

StatisticsCollection::StatisticsCollection() {
  container_.push_back(new StatisticsItems012());
  container_.push_back(new StatisticsItems01());
  container_.push_back(new StatisticsItems12());
  container_.push_back(new StatisticsItems02());
  container_.push_back(new StatisticsItems0());
  container_.push_back(new StatisticsItems1());
  container_.push_back(new StatisticsItems2());
}

StatisticsCollection::~StatisticsCollection() {
  for (auto *statisticsItems : container_) {
    delete statisticsItems;
  }
}

void StatisticsCollection::Add(const StatisticsUnit &newItem) {
  for (size_t i=0; i < container_.size(); ++i) {
    container_[i]->Add(newItem);
  }
}

void StatisticsCollection::Shrink() {
  ShrinkCommon_();
  ShrinkNoDominator_();
}

bool StatisticsCollection::operator==(const StatisticsCollection &other) const {
  if (container_.size() != other.container_.size()) {
    return false;
  }

  for (auto *statisticsItem : container_) {
    bool ret = false;
    for (auto *statisticsItem1 : other.container_) {
      if (*statisticsItem == *statisticsItem1) {
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

int StatisticsCollection::Load(const std::string &str) {
  container_.clear();

  std::vector<std::string> items;
  StrHelper::SplitStr(str, kSep, items);
  for (auto &str : items) {
    if (str.empty()) {
      break;
    }

    StatisticsItems *statisticsItems = StatisticsItems::Load(str);
    if (nullptr!=statisticsItems) {
      container_.push_back(statisticsItems);
    } else {
      return -1;
    }
  }
  return 0;
}

void StatisticsCollection::Dump(std::stringstream &ss) const {
  for (auto *statisticsItems : container_) {
    statisticsItems->Dump(ss);
    ss << kSep;
  }
}

void StatisticsCollection::ShrinkCommon_() {
  size_t countAll = 0;
  for (auto *statisticsItems : container_) {
    if (statisticsItems->GetCategory() == StatisticsItems::kCategory012 &&
        statisticsItems->Size() == 1) {
      countAll = statisticsItems->GetCount();
      break;
    }
  }

  if (0 == countAll) {
    return;
  }

  for (auto *statisticsItems : container_) {
    if (statisticsItems->GetCount() != countAll ||
        statisticsItems->Size() != 1) {
      return;
    }
  }

  auto iter = container_.begin();
  while (iter != container_.end()) {
    if ((*iter)->GetCategory() != StatisticsItems::kCategory012) {
      iter = container_.erase(iter);
    } else {
      ++iter;
    }
  }
}

void StatisticsCollection::ShrinkNoDominator_() {
  auto iter = container_.begin();
  while (iter != container_.end()) {
    if ((*iter)->GetDominator() == nullptr) {
      delete *iter;
      iter = container_.erase(iter);
    } else {
      ++iter;
    }
  }
}

}}}
