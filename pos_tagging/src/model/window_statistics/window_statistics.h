#pragma once

#include "../../public.h"
#include "feature_comb.h"
#include "statistics_unit.h"
#include "statistics_collection.h"
#include "window_feature.h"

namespace xforce { namespace nlu { namespace pos {

class WindowStatistics {
 public:
  WindowStatistics();
  virtual ~WindowStatistics();

 public:
  inline std::pair<StatisticsItems::Category, const StatisticsUnit*> GetDominator(
          const std::wstring &item0,
          const std::wstring &item1) const;

  inline std::pair<StatisticsItems::Category, const StatisticsUnit*> GetDominator(
          const std::wstring &item0,
          const std::wstring &item1,
          const std::wstring &item2) const;

  void Shrink();
  size_t Size() const { return statistics_.size(); }

 public:
  static WindowStatistics* Create(const std::string &filepath);

 private:
  inline std::pair<StatisticsItems::Category, const StatisticsUnit*>
          GetDominatorFromFeatures_(const std::vector<FeatureComb3> &featureCombs) const;

  void Add_(const std::vector<std::pair<std::wstring, basic::PosTag::Type::Val >> &pairs);
  void ActualAdd_(const FeatureComb3 &key, const StatisticsUnit &newItem);

 private:
  WindowFeaturesExtractor windowFeaturesExtractor_;
  std::unordered_map<FeatureComb3, StatisticsCollection*, HashFeatureComb3> statistics_;

  mutable std::vector<FeatureComb3> tmpFeatureCombs_;
};

std::pair<StatisticsItems::Category, const StatisticsUnit*> WindowStatistics::GetDominator(
        const std::wstring &item0,
        const std::wstring &item1) const {
  tmpFeatureCombs_.clear();
  windowFeaturesExtractor_.Enum(item0, item1, tmpFeatureCombs_);
  return GetDominatorFromFeatures_(tmpFeatureCombs_);
}

std::pair<StatisticsItems::Category, const StatisticsUnit*> WindowStatistics::GetDominator(
        const std::wstring &item0,
        const std::wstring &item1,
        const std::wstring &item2) const {
  tmpFeatureCombs_.clear();
  windowFeaturesExtractor_.Enum(item0, item1, item2, tmpFeatureCombs_);
  return GetDominatorFromFeatures_(tmpFeatureCombs_);
}

std::pair<StatisticsItems::Category, const StatisticsUnit*>
        WindowStatistics::GetDominatorFromFeatures_(const std::vector<FeatureComb3> &featureCombs) const {
  for (auto &featureComb : featureCombs) {
    auto iter = statistics_.find(featureComb);
    if (iter == statistics_.end()) {
      continue;
    }

    auto result = iter->second->GetDominator();
    if (result.first != StatisticsItems::kOther) {
      return result;
    }
  }
  return std::make_pair(StatisticsItems::kOther, nullptr);
}

}}}
