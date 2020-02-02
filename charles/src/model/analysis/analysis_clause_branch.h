#pragma once

#include "public.h"
#include "analysis_component.h"
#include "nlu_context_split.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class AnalysisClauseBranch {
 public:
  AnalysisClauseBranch(
          ssize_t no,
          const basic::NluContext &nluContext,
          const SplitStage &splitStage,
          const basic::CollectionSyntaxTag &endTags,
          const std::string &verifyStrategy = "null",
          bool traceEvent=true);

  virtual ~AnalysisClauseBranch();

  bool Process(std::queue<std::shared_ptr<AnalysisClauseBranch>> &children);

  size_t GetNo() const { return no_; }
  size_t GetNoFather() const { return no_/100; }
  const std::shared_ptr<basic::NluContext>& GetNluContext() const { return nluContext_; }
  const SplitStage& GetSplitStage() const { return *splitStage_; }
  bool GetEnd() const { return end_; }
  basic::SyntaxTag::Type::Val GetTheEndTag() const { return theEndTag_; }
  inline bool IsMainAnalysis() const;

  void Dump(JsonType &jsonType);

 private:
  bool AllChildrenEnd_();
  bool IsFinished_(basic::NluContext &nluContext);
  int VerifySubBranches_();

 private:
  ssize_t no_;
  std::shared_ptr<basic::NluContext> nluContext_;
  std::list<std::shared_ptr<AnalysisClauseBranch>> children_;
  SplitStage *splitStage_;
  basic::CollectionSyntaxTag endTags_;
  std::string verifyStrategy_;
  bool traceEvent_;

  bool processed_;
  bool end_;
  size_t childrenIdx_;
  basic::SyntaxTag::Type::Val theEndTag_;
};

bool AnalysisClauseBranch::IsMainAnalysis() const {
  return endTags_.IsStc();
}

}}}
