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

void StatisticsCollection::Dump(std::stringstream &ss) const {
  for (auto *statisticsItems : container_) {
    statisticsItems->Dump(ss);
    ss << kSep;
  }
}

}}}
