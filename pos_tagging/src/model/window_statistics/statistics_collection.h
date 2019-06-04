#pragma once

#include "../../public.h"
#include "statistics_items.h"

namespace xforce { namespace nlu { namespace pos {

class StatisticsCollection {
 public:
  StatisticsCollection();
  virtual ~StatisticsCollection();

  void Add(const StatisticsUnit &newItem);
  inline std::pair<StatisticsItems::Category, const StatisticsUnit*> GetDominator() const;
  void Shrink();
  size_t Size() const { return container_.size(); }

 private:
  std::vector<StatisticsItems*> container_;
};

std::pair<StatisticsItems::Category, const StatisticsUnit*> StatisticsCollection::GetDominator() const {
  for (auto *statisticsItems : container_) {
    auto *dominator = statisticsItems->GetDominator();
    if (nullptr != dominator) {
      return std::make_pair(statisticsItems->GetCategory(), dominator);
    }
  }
  return std::make_pair(StatisticsItems::kOther, nullptr);
}

}}}
