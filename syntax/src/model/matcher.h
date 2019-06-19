#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace syntax {

class Matcher {
 private:
  static const std::wstring kSyntacticStoragePrefix;

 public:
  Matcher();

  bool Init();
  void Match(basic::NluContext &nluContext);

  virtual ~Matcher();

 private:
  bool SyntaxProcessForChunkSep_(basic::NluContext &nluContext);
  bool SyntaxProcessForChunk_(basic::NluContext &nluContext);

 private:
  milkie::Milkie *milkie_;
  std::shared_ptr<milkie::FeatureExtractor> feChunkSep_;
  std::shared_ptr<milkie::FeatureExtractor> feChunk_;
};

}}}
