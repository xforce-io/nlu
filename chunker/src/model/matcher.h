#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace chunker {

class FilterParserCommon;

class Matcher {
 private:
  static const std::wstring kChunkStoragePrefix;
  static const std::wstring kSyntacticStoragePrefix;

 public:
  Matcher();
  virtual ~Matcher();

  bool Init();
  void Match(std::shared_ptr<basic::NluContext> nluContext);

 private:
  void ParseAccordingToRule_(std::shared_ptr<basic::NluContext> nluContext);
  void ParseCommon_(basic::NluContext &nluContext);

 private:
  milkie::Milkie *parser_;
  std::shared_ptr<milkie::FeatureExtractor> featureExtractor_;
  std::vector<FilterParserCommon*> filterParserCommons_;
};

}}}
