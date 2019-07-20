#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class NluContextSplit {
 public:
  NluContextSplit();
  virtual ~NluContextSplit();

  bool Init();

  bool Split(
          const basic::NluContext &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts,
          basic::Stage::Val stage);

 private:
  bool SplitBySegment_(
          const basic::NluContext &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  bool SplitBySyntax_(
          const basic::NluContext &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  void AdjustSegTags_(
          const basic::NluContext &nluContext,
          size_t i,
          basic::PosTag::Type::Val posTag);

 private:
  milkie::Milkie *splitRuleEngine_;
};

}}}
