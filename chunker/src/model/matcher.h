#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher {
 private:
  static const std::wstring kChunkStoragePrefix;

 public:
  Matcher();

  bool Init();
  void Match(basic::NluContext &nluContext);

  virtual ~Matcher();

 private:
  milkie::Milkie *milkie_;
  std::shared_ptr<milkie::FeatureExtractor> featureExtractor_;
};

}}}
