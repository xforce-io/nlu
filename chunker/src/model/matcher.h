#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher {
 public:
  Matcher();

  bool Init();
  void Match(const std::wstring &query);

  virtual ~Matcher();

 private:
  milkie::Milkie *milkie_;
  std::shared_ptr<milkie::FeatureExtractor> featureExtractor_;
};

}}}
