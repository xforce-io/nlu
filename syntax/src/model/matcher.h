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
  void AppendixProcess_(std::shared_ptr<basic::NluContext> nluContext);

 private:
  bool RuleContNp_(
          std::shared_ptr<basic::NluContext> nluContext,
          const std::shared_ptr<basic::Chunk> &chunk);

  bool RuleIntransitiveVerb_(
          std::shared_ptr<basic::NluContext> nluContext,
          const std::shared_ptr<basic::Chunk> &chunk);

  void AddAdvpDescDir_(std::shared_ptr<basic::NluContext> nluContext);
  void AddAdvpDescDirForChunk_(
          std::shared_ptr<basic::NluContext> nluContext,
          std::shared_ptr<basic::Chunk> advp);

  void AnalysisAdj_(
          std::shared_ptr<basic::NluContext> &nluContext,
          std::shared_ptr<basic::Chunk> advp,
          std::shared_ptr<basic::Segment> adj,
          int &descLeft,
          int &descRight,
          int &leftBound,
          int &rightBound);

 private:
  milkie::Milkie *milkie_;
  std::shared_ptr<milkie::FeatureExtractor> feChunkSep_;
  std::shared_ptr<milkie::FeatureExtractor> feChunk_;
};

}}}