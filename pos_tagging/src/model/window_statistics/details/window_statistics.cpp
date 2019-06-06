#include "../window_statistics.h"

namespace xforce { namespace nlu { namespace pos {

const std::string WindowStatistics::kFilepathCache = "/tmp/_win_stat_cache";

WindowStatistics::WindowStatistics() :
  statistics_(1024*1024*10) {}

WindowStatistics::~WindowStatistics() {
  Clear();
}

WindowStatistics* WindowStatistics::Create(const std::string &filepath) {
  auto windowStatistics = new WindowStatistics();

  Timer timer;
  int ret = windowStatistics->LoadFromFile(kFilepathCache);
  if (ret==0) {
    timer.Stop(true);
    NOTICE("win_stat_load_from_cache_cost[" << timer.TimeSec() << "]");
    return windowStatistics;
  }

  std::vector<std::string> lines;
  bool retb = IOHelper::ReadLinesFromFilepath(filepath, lines);
  if (!retb) {
    return nullptr;
  }

  std::vector<std::pair<std::wstring, basic::PosTag::Type::Val>> pairs;
  for (auto &line : lines) {
    auto wline = StrHelper::Str2Wstr(line);
    if (wline == nullptr) {
      FATAL("fail_str_2_wstr[" << wline << "]");
      continue;
    }

    std::vector<std::wstring> strs;
    StrHelper::SplitStr(*wline, std::wstring(L"  "), strs);
    for (size_t i=1; i < strs.size(); ++i) {
      if (strs[i].empty()) {
        continue;
      }

      std::vector<std::wstring> pair;
      StrHelper::SplitStr(strs[i], L'/', pair);
      if (pair.size() == 2) {
        if (pair[0].empty()) {
          break;
        }

        pairs.push_back(std::make_pair(
                pair[0],
                basic::PosTag::GetPosTag(pair[1])));
      } else {
        FATAL("invalid_window_statistics_item[" << strs[i] << "]");
      }
    }
  }

  windowStatistics->Add_(pairs);
  windowStatistics->Shrink();
  ret = windowStatistics->DumpToFile(kFilepathCache);
  if (ret!=0) {
    return nullptr;
  }
  return windowStatistics;
}

void WindowStatistics::Shrink() {
  auto iter = statistics_.begin();
  while (iter != statistics_.end()) {
    iter->second->Shrink();
    if (iter->second->Size() == 0) {
      delete iter->second;
      iter = statistics_.erase(iter);
    } else {
      ++iter;
    }
  }
}

bool WindowStatistics::operator==(const WindowStatistics &other) const {
  if (statistics_.size() != other.statistics_.size()) {
    return false;
  }

  for (auto &pair : statistics_) {
    auto iter = other.statistics_.find(pair.first);
    if (iter == other.statistics_.end() ||
        !(*iter->second == *pair.second)) {
      return false;
    }
  }
  return true;
}

void WindowStatistics::Clear() {
  for (auto iter = statistics_.begin(); iter != statistics_.end(); ++iter) {
    delete iter->second;
  }
  statistics_.clear()
  ;
}

int WindowStatistics::Load(const std::string &str) {
  ssize_t curPos = 0;
  while (curPos != ssize_t(str.length() - 1)) {
    ssize_t nextPos = str.find('|', curPos);
    if (nextPos<0) {
      break;
    }

    std::string tmpStr = str.substr(curPos, nextPos-curPos);

    std::vector<std::string> items;
    StrHelper::SplitStr(tmpStr, '-', items);

    FeatureComb3 featureComb3;
    int ret = featureComb3.Load(items[0]);
    if (ret != 0) {
      return -2;
    }

    auto *statisticsCollection = new StatisticsCollection();
    ret = statisticsCollection->Load(items[1]);
    if (ret != 0) {
      return -3;
    }

    statistics_.insert(std::make_pair(featureComb3, statisticsCollection));
    curPos = nextPos+1;
  }
  return 0;
}

int WindowStatistics::LoadFromFile(const std::string &filepath) {
  FILE *fp = fopen(filepath.c_str(), "r");
  if (nullptr == fp) {
    return -1;
  }

  std::string str;
  char buf[4096];
  ssize_t n = fread(buf, sizeof(buf), 1, fp);
  if (n>0) {
    str.append(buf);
  }
  return Load(str);
}

void WindowStatistics::Dump(std::stringstream &ss) const {
  for (auto &pair : statistics_) {
    pair.first.Dump(ss);
    ss << '-';
    pair.second->Dump(ss);
    ss << '|';
  }
}

int WindowStatistics::DumpToFile(const std::string &filepath) {
  std::ofstream outFile(filepath);
  if (!outFile) {
    FATAL("fail_open_dump_file[" << *StrHelper::Str2Wstr(filepath) << "]");
    return -1;
  }

  std::stringstream ss;
  Dump(ss);
  outFile << ss.rdbuf();
  outFile.close();
  return 0;
}

void WindowStatistics::Add_(
        const std::vector<std::pair<std::wstring, basic::PosTag::Type::Val >> &pairs) {
  for (size_t i=0; i < pairs.size()-1; ++i) {
    tmpFeatureCombs_.clear();
    windowFeaturesExtractor_.Enum(pairs[i].first, pairs[i+1].first, tmpFeatureCombs_);
    for (auto &featureComb : tmpFeatureCombs_) {
      ActualAdd_(
              featureComb,
              StatisticsUnit(
                      pairs[i].second,
                      pairs[i+1].second));
    }
  }

  for (size_t i=0; i < pairs.size()-2; ++i) {
    tmpFeatureCombs_.clear();
    windowFeaturesExtractor_.Enum(pairs[i].first, pairs[i+1].first, pairs[i+2].first, tmpFeatureCombs_);
    for (auto &featureComb : tmpFeatureCombs_) {
      ActualAdd_(
              featureComb,
              StatisticsUnit(
                      pairs[i].second,
                      pairs[i+1].second,
                      pairs[i+2].second));
    }
  }
}

void WindowStatistics::ActualAdd_(
        const FeatureComb3 &key,
        const StatisticsUnit &newItem) {
  auto iter = statistics_.find(key);
  if (iter != statistics_.end()) {
    iter->second->Add(newItem);
  } else {
    StatisticsCollection *statisticsCollection = new StatisticsCollection();
    statisticsCollection->Add(newItem);
    statistics_.insert(std::make_pair(key, statisticsCollection));
  }
}

}}}
