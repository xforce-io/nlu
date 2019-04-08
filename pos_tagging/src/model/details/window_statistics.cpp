#include "../window_statistics.h"

namespace xforce { namespace nlu { namespace pos {

WindowStatistics::~WindowStatistics() {
  for (auto iter = statistics_.begin(); iter != statistics_.end(); ++iter) {
    delete iter->second;
  }
}

WindowStatistics* WindowStatistics::Create(const std::string &filepath) {
  std::vector<std::string> lines;
  bool ret = IOHelper::ReadLinesFromFilepath(filepath, lines);
  if (!ret) {
    return nullptr;
  }

  std::vector<std::pair<std::wstring, basic::PosTag::Type>> pairs;
  for (auto &line : lines) {
    auto wline = StrHelper::Str2Wstr(line);
    std::vector<std::wstring> strs;
    StrHelper::SplitStr(*wline, std::wstring(L"  "), strs);
    for (size_t i=1; i < strs.size(); ++i) {
      std::vector<std::wstring> pair;
      StrHelper::SplitStr(strs[i], L'/', pair);
      pairs.push_back(std::make_pair(
              pair[0],
              basic::PosTag::GetPosTag(pair[1])));
    }
  }

  auto windowStatistics = new WindowStatistics();
  windowStatistics->Add_(pairs);
  return windowStatistics;
}

void WindowStatistics::Add_(
        const std::vector<std::pair<std::wstring, basic::PosTag::Type >> &pairs) {
  for (size_t i=0; i < pairs.size()-1; ++i) {
    ActualAdd_(
            pairs[i].first + L"-" + pairs[i+1].first,
            StatisticsItem(
                    pairs[i].second,
                    pairs[i+1].second));
  }

   for (size_t i=0; i < pairs.size()-2; ++i) {
    ActualAdd_(
            pairs[i].first + L"-" + pairs[i+1].first + L"-" + pairs[i+2].first,
            StatisticsItem(
                    pairs[i].second,
                    pairs[i+1].second,
                    pairs[i+2].second));
  }
}

void WindowStatistics::ActualAdd_(
        const std::wstring &key,
        const StatisticsItem &newItem) {
  auto iter = statistics_.find(key);
  if (iter != statistics_.end()) {
    auto statisticsItems = iter->second;
    for (auto &statisticsItem : statisticsItems->GetItems()) {
      if (statisticsItem.SameType(newItem)) {
        ++statisticsItem.count;
      }
    }
  } else {
    auto statisticsItems = new StatisticsItems();
    statisticsItems->Add(StatisticsItem(newItem));
    statistics_.insert(std::make_pair(key, statisticsItems));
  }
}

}}}
