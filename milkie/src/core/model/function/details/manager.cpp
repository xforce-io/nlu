#include "../manager.h"
#include "../../../../conf/conf.h"
#include "../feature_extractor/feature_extractor.h"

namespace xforce { namespace nlu { namespace milkie {

std::shared_ptr<Manager> Manager::manager_;

Manager::Manager(std::unordered_map<std::wstring, std::shared_ptr<FeatureExtractor>> featureExtractors) :
  featureExtractors_(featureExtractors) {}

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

std::shared_ptr<FeatureExtractor> Manager::GetGlobalFeatureExtractor(const std::wstring &name) {
  return manager_->GetFeatureExtractor(name);
}

void Manager::SetGlobalManager(std::shared_ptr<Manager> manager) {
  manager_ = manager;
}

std::shared_ptr<Manager> Manager::BuildGlobalManager() {
  return Build(Conf::Get().GetReferFilepaths());
}

std::shared_ptr<Manager> Manager::Build(const std::vector<std::string> &filepaths) {
  std::unordered_map<std::wstring, std::shared_ptr<FeatureExtractor>> results;
  for (auto &filepath : filepaths) {
    std::vector<std::shared_ptr<FeatureExtractor>> featureExtractors;
    auto ret = FeatureExtractor::Build(filepath, featureExtractors);
    if (ret) {
      for (auto &featureExtractor : featureExtractors) {
        results.insert(std::make_pair(featureExtractor->GetName(), featureExtractor));
      }
    }
  }
  return std::make_shared<Manager>(results);
}

}}}
