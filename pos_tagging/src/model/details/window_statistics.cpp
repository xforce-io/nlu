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

  for (auto &line : lines) {
    auto wline = StrHelper::Str2Wstr(line);
    std::vector<std::wstring> strs;
    StrHelper::SplitStr(*wline, L"  ", strs);
    for (size_t i=1; i < strs.size(); ++i) {
      std::vector<std::wstring> pair;
      StrHelper::SplitStr(strs[i], L'/', pair);
      basic::PosTag::GetPosTag(pair[1]);
    }
  }
}

void WindowStatistics::Add_(
        const std::wstring &word0,
        const std::wstring &word1,
        basic::PosTag::Type type0,
        basic::PosTag::Type type1) {
  std::wstring key = word0 + L"-" + word1;
  StatisticsItem newItem(type0, type1);
  ActualAdd_(key, newItem);
}

void WindowStatistics::Add_(
        const std::wstring &word0,
        const std::wstring &word1,
        const std::wstring &word2,
        basic::PosTag::Type type0,
        basic::PosTag::Type type1,
        basic::PosTag::Type type2) {
  std::wstring key = word0 + L"-" + word1 + L"-" + word2;
  StatisticsItem newItem(type0, type1, type2);
  ActualAdd_(key, newItem);
}

void WindowStatistics::ActualAdd_(
        const std::wstring &key,
        const StatisticsItem &newItem) {
  auto iter = statistics_.find(key);
  if (iter != statistics_.end()) {
    StatisticsItems *statisticsItems = iter->second;
    for (auto &statisticsItem : *statisticsItems) {
      if (statisticsItem.SameType(newItem)) {
        ++statisticsItem.count;
      }
    }
  } else {
    StatisticsItems *statisticsItems = new StatisticsItems();
    statisticsItems->push_back(StatisticsItem(newItem));
    statistics_.insert(std::make_pair(key, statisticsItems));
  }
}

}}}
