#pragma once

#include "../../public.h"
#include "statistics_unit.h"
#include "statistics_collection.h"

namespace xforce { namespace nlu { namespace pos {

class WindowStatistics {
 public:
  WindowStatistics() {}
  virtual ~WindowStatistics();

 public:
  inline std::pair<StatisticsItems::Category, const StatisticsUnit*> GetDominator(
          const std::wstring &item0,
          const std::wstring &item1) const;

  inline std::pair<StatisticsItems::Category, const StatisticsUnit*> GetDominator(
          const std::wstring &item0,
          const std::wstring &item1,
          const std::wstring &item2) const;

 public:
  static WindowStatistics* Create(const std::string &filepath);

 private:
  void Add_(const std::vector<std::pair<std::wstring, basic::PosTag::Type >> &pairs);

  void ActualAdd_(const std::wstring &key, const StatisticsUnit &newItem);

 private:
  std::unordered_map<std::wstring, StatisticsCollection*> statistics_;
};

std::pair<StatisticsItems::Category, const StatisticsUnit*> WindowStatistics::GetDominator(
        const std::wstring &item0,
        const std::wstring &item1) const {
  std::wstring tmpKey = item0 + L"-" + item1;
  auto iter = statistics_.find(tmpKey);
  if (iter == statistics_.end()) {
    return std::make_pair(StatisticsItems::kOther, nullptr);
  }
  return iter->second->GetDominator();
}

std::pair<StatisticsItems::Category, const StatisticsUnit*> WindowStatistics::GetDominator(
        const std::wstring &item0,
        const std::wstring &item1,
        const std::wstring &item2) const {
  std::wstring tmpKey = item0 + L"-" + item1 + L"-" + item2;
  auto iter = statistics_.find(tmpKey);
  if (iter == statistics_.end()) {
    return std::make_pair(StatisticsItems::kOther, nullptr);
  }
  return iter->second->GetDominator();
}

}}}
