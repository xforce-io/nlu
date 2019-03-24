#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace milkie {

class FeatureExtractor;
class Conf;

class Manager {
 public:
  bool Init(const std::vector<std::string> &referFilepaths);

  std::shared_ptr<FeatureExtractor> GetFeatureExtractor(const std::wstring &name);
  void PutFeatureExtractor(const std::wstring &name, std::shared_ptr<FeatureExtractor> featureExtractor);

 private:
  std::unordered_map<std::wstring, std::shared_ptr<FeatureExtractor>> featureExtractors_;
};

}}}
