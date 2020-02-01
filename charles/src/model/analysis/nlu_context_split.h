#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class NluContextSplit {
 private:
  static const size_t kMaxNumBranches = 3;
  static const std::wstring kBranch0SyntaxStoragePrefix;
  static const std::wstring kBranch1SyntaxStoragePrefix;
  static const std::wstring kBranch2SyntaxStoragePrefix;

 public:
  NluContextSplit();
  virtual ~NluContextSplit();

  bool Init();

  void Split(
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts,
          basic::Stage::Val stage);

 private:
  void SplitByPosTag_(
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts);

  void SplitBySyntax_(
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts);

  void AdjustSegTags_(
          const basic::NluContext &nluContext,
          size_t i,
          basic::PosTag::Type::Val posTag);

 private:
  milkie::Milkie *splitRuleEngine_;
  std::shared_ptr<milkie::FeatureExtractor> feNluContextSplit_;
};

}}}
