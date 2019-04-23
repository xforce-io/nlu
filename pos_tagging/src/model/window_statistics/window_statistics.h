#pragma once

#include "../../public.h"
#include "statistics_unit.h"
#include "statistics_items.h"

namespace xforce { namespace nlu { namespace pos {

class StatisticsCollection {
 public:
  StatisticsCollection() {}

 private:
  std::vector<StatisticsItems*> statisticsitems_;
  size_t count_;
};

class WindowStatistics {
 public:
  WindowStatistics() {}
  virtual ~WindowStatistics();

 public:
  inline StatisticsItems* Get(
          const std::wstring &item0,
          const std::wstring &item1);

  inline StatisticsItems* Get(
          const std::wstring &item0,
          const std::wstring &item1,
          const std::wstring &item2);

 public:
  static WindowStatistics* Create(const std::string &filepath);

 private:
  void Add_(const std::vector<std::pair<std::wstring, basic::PosTag::Type >> &pairs);

  void ActualAdd_(const std::wstring &key, const StatisticsUnit &newItem);

 private:
  std::unordered_map<std::wstring, StatisticsItems*> statistics_;
};

StatisticsItems* WindowStatistics::Get(
        const std::wstring &item0,
        const std::wstring &item1) {
  std::wstring tmpKey = item0 + L"-" + item1;
  auto iter = statistics_.find(tmpKey);
  if (iter != statistics_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

StatisticsItems* WindowStatistics::Get(
        const std::wstring &item0,
        const std::wstring &item1,
        const std::wstring &item2) {
  std::wstring tmpKey = item0 + L"-" + item1 + L"-" + item2;
  auto iter = statistics_.find(tmpKey);
  if (iter != statistics_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

}}}
