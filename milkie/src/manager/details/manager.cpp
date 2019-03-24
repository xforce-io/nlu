#include "../manager.h"
#include "../../conf/conf.h"
#include "../../core/model/feature_extractor/feature_extractor.h"

namespace xforce { namespace nlu { namespace milkie {

bool Manager::Init(const std::vector<std::string> &referFilepaths) {
  featureExtractors_.clear();
  for (auto &filepath : referFilepaths) {
    std::vector<std::shared_ptr<FeatureExtractor>> featureExtractors;
    auto ret = FeatureExtractor::Build(filepath, featureExtractors);
    if (ret) {
      for (auto &featureExtractor : featureExtractors) {
        featureExtractors_.insert(std::make_pair(featureExtractor->GetName(), featureExtractor));
      }
    }
  }
  return true;
}

std::shared_ptr<FeatureExtractor> Manager::GetFeatureExtractor(const std::wstring &name) {
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
