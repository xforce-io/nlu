#pragma once

#include "public.h"
#include "analysis_component.h"
#include "nlu_context_split.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class AnalysisClauseBranch {
 public:
  AnalysisClauseBranch(
          size_t no,
          const std::wstring &clause,
          const SplitStage &splitStage);

  AnalysisClauseBranch(
          size_t no,
          const basic::NluContext &nluContext,
          const SplitStage &splitStage);

  virtual ~AnalysisClauseBranch();

  bool Process(std::queue<std::shared_ptr<AnalysisClauseBranch>> &children);

  size_t GetNo() const { return no_; }
  const std::shared_ptr<basic::NluContext>& GetNluContext() const { return nluContext_; }
  const SplitStage& GetSplitStage() const { return *splitStage_; }
  bool GetEnd() const { return end_; }

  void Dump(JsonType &jsonType);

 private:
  bool AllChildrenEnd_();
  static bool IsFinished_(basic::NluContext &nluContext);

 private:
  size_t no_;
  std::shared_ptr<basic::NluContext> nluContext_;
  std::list<std::shared_ptr<AnalysisClauseBranch>> children_;
  SplitStage *splitStage_;
  bool processed_;
  bool end_;
};

}}}