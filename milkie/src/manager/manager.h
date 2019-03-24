#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace milkie {

class FeatureExtractor;
class Conf;
class ReferManager;

class Manager {
 public:
  bool Init(const Conf &conf, ReferManager &referManager);

  std::shared_ptr<FeatureExtractor> GetFeatureExtractor(const std::wstring &name);
  void PutFeatureExtractor(const std::wstring &name, std::shared_ptr<FeatureExtractor> featureExtractor);

 private:
  ReferManager *referManager_;

  std::unordered_map<std::wstring, std::shared_ptr<FeatureExtractor>> featureExtractors_;
};

}}}
