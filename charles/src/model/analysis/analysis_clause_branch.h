#pragma once

#include "public.h"
#include "analysis_component.h"
#include "nlu_context_split.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClauseBranch {
 public:
  AnalysisClauseBranch(
          NluContextSplit &nluContextSplit,
          size_t no,
          const std::wstring &clause);

  AnalysisClauseBranch(
          NluContextSplit &nluContextSplit,
          size_t no,
          const basic::NluContext &nluContext);

  bool Process(std::queue<std::shared_ptr<AnalysisClauseBranch>> &children);
  std::shared_ptr<AnalysisClauseBranch> Clone() const;

  size_t GetNo() const { return no_; }
  const std::shared_ptr<basic::NluContext>& GetNluContext() const { return nluContext_; }

  void Dump(JsonType &jsonType);

 private:
  bool AllChildrenEnd_();
  static bool IsFinished_(basic::NluContext &nluContext);

 private:
  NluContextSplit *nluContextSplit_;
  size_t no_;
  std::shared_ptr<basic::NluContext> nluContext_;
  std::unordered_map<basic::Stage::Val, std::shared_ptr<AnalysisClauseBranch>> ancestors_;
  std::list<std::shared_ptr<AnalysisClauseBranch>> children_;
  basic::Stage::Val splitStage_;
  bool processed_;
  bool end_;
};

}}}