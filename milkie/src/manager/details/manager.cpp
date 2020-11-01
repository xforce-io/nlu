#include "../manager.h"
#include "../../conf/conf.h"
#include "../../core/model/feature_extractor/feature_extractor.h"
#include "../../core/model/refer/refer_manager.h"

namespace xforce { namespace nlu { namespace milkie {

bool Manager::Init(
        const Conf &conf,
        ReferManager &referManager) {
  referManager_ = &referManager;
  featureExtractors_.clear();
  for (auto &filepath : conf.GetExprFilepaths()) {
    std::vector<std::shared_ptr<FeatureExtractor>> featureExtractors;
    auto ret = FeatureExtractor::Build(conf, *referManager_, filepath, featureExtractors);
    if (ret) {
      for (auto &featureExtractor : featureExtractors) {
        featureExtractors_.insert(std::make_pair(featureExtractor->GetName(), featureExtractor));
      }
    }
  }
  return true;
}

const std::shared_ptr<FeatureExtractor> Manager::GetFeatureExtractor(const std::wstring &name) const {
  auto iter = featureExtractors_.find(name);
  if (featureExtractors_.end() != iter) {
    return iter->second;
  } else {
    return nullptr;
  }
}

void Manager::PutFeatureExtractor(const std::wstring &name, std::shared_ptr<FeatureExtractor> featureExtractor) {
  featureExtractors_.insert(std::make_pair(name, featureExtractor));
}

}}}
