#pragma once

#include "public.h"
#include "analysis_component.h"
#include "nlu_context_split.h"
#include "sub_branch.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;

class AnalysisClauseBranch {
 public:
  AnalysisClauseBranch(
          size_t no,
          const basic::NluContext &nluContext,
          const SplitStage &splitStage,
          basic::SyntaxTag::Type::Val endTag = basic::SyntaxTag::Type::kStc,
          const std::string &verifyStrategy = "null",
          bool traceEvent=true);

  virtual ~AnalysisClauseBranch();

  bool Process(std::queue<std::shared_ptr<AnalysisClauseBranch>> &children);

  size_t GetNo() const { return no_; }
  size_t GetNoFather() const { return no_/100; }
  const std::shared_ptr<basic::NluContext>& GetNluContext() const { return nluContext_; }
  const SplitStage& GetSplitStage() const { return *splitStage_; }
  bool GetEnd() const { return end_; }

  void Dump(JsonType &jsonType);

 private:
  bool AllChildrenEnd_();
  bool IsFinished_(basic::NluContext &nluContext);
  int VerifySubBranches_();

 private:
  size_t no_;
  std::shared_ptr<basic::NluContext> nluContext_;
  std::list<std::shared_ptr<AnalysisClauseBranch>> children_;
  SplitStage *splitStage_;
  basic::SyntaxTag::Type::Val endTag_;
  std::string verifyStrategy_;
  bool traceEvent_;

  std::vector<SubBranch*> subBranches_;

  bool processed_;
  bool end_;
  size_t childrenIdx_;
};

}}}
