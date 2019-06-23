#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace syntax {

class Matcher {
 private:
  static const std::wstring kSyntacticStoragePrefix;

 public:
  Matcher();

  bool Init();
  void Match(std::shared_ptr<basic::NluContext> nluContext);

  virtual ~Matcher();

 private:
  bool Process_(std::shared_ptr<basic::NluContext> nluContext);

  bool SyntaxProcessForChunkSep_(std::shared_ptr<basic::NluContext> nluContext);
  bool SyntaxProcessForChunk_(std::shared_ptr<basic::NluContext> nluContext);
  bool PostProcess_(std::shared_ptr<basic::NluContext> nluContext);

 private:
  milkie::Milkie *milkie_;
  std::shared_ptr<milkie::FeatureExtractor> feChunkSep_;
  std::shared_ptr<milkie::FeatureExtractor> feChunk_;
};

}}}
