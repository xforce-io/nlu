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
  for (auto *statisticsItems : container_) {
    statisticsItems->Add(newItem);
  }
}


}}}
