#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace milkie {

class FeatureExtractor;
class Conf;
class ReferManager;

class Manager {
 public:
  bool Init(const Conf &conf, ReferManager &referManager);

  const std::shared_ptr<FeatureExtractor> GetFeatureExtractor(const std::wstring &name) const;
  void PutFeatureExtractor(const std::wstring &name, std::shared_ptr<FeatureExtractor> featureExtractor);

 private:
  ReferManager *referManager_;

  std::unordered_map<std::wstring, std::shared_ptr<FeatureExtractor>> featureExtractors_;
};

}}}
