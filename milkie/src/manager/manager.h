#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace milkie {

class FeatureExtractor;

class Manager {
 public:
  explicit Manager(std::unordered_map<std::wstring, std::shared_ptr<FeatureExtractor>> featureExtractors);

  std::shared_ptr<FeatureExtractor> GetFeatureExtractor(const std::wstring &name);
  void PutFeatureExtractor(const std::wstring &name, std::shared_ptr<FeatureExtractor> featureExtractor);

 public:
  static std::shared_ptr<FeatureExtractor> GetGlobalFeatureExtractor(const std::wstring &name);
  static void SetGlobalManager(std::shared_ptr<Manager> manager);
  static std::shared_ptr<Manager> BuildGlobalManager();
  static std::shared_ptr<Manager> Build(const std::vector<std::string> &filepaths);

 private:
  std::unordered_map<std::wstring, std::shared_ptr<FeatureExtractor>> featureExtractors_;

  static std::shared_ptr<Manager> manager_;
};

}}}
