#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher {
 private:
  static const std::wstring kChunkStoragePrefix;
  static const std::wstring kSyntacticStoragePrefix;

 public:
  Matcher();

  bool Init();
  void Match(std::shared_ptr<basic::NluContext> nluContext);

  virtual ~Matcher();

 private:
  void ParseCommon_(basic::NluContext &nluContext);
  void ParseAccordingToRule_(std::shared_ptr<basic::NluContext> nluContext);

 private:
  milkie::Milkie *milkie_;
  std::shared_ptr<milkie::FeatureExtractor> featureExtractor_;
};

}}}
