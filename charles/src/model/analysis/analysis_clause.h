#pragma once

#include "public.h"
#include "analysis_component.h"

namespace xforce { namespace nlu { namespace charles {

class SplitRuleMgr;
class AnalysisClauseBranch;

class AnalysisClause : public AnalysisComponent {
 public:
  typedef std::shared_ptr<AnalysisClauseBranch> Branch;
  typedef std::list<Branch> Branches;

 public:
  AnalysisClause(
          std::shared_ptr<basic::NluContext> nluContext,
          const basic::CollectionSyntaxTag &endTags,
          const std::string &verifyStrategy = "null",
          bool traceEvent=true);

  AnalysisClause(
          const std::wstring &clause,
          const basic::CollectionSyntaxTag &endTags,
          const std::string &verifyStrategy = "null",
          bool traceEvent=true);

  virtual ~AnalysisClause();

  bool Init();
  bool Process();
  inline const std::shared_ptr<basic::NluContext>& GetClause() const;
  inline std::shared_ptr<basic::NluContext>& GetClause();
  const std::shared_ptr<basic::CollectionSyntaxTag> GetEndTags() const { return endTags_; }
  std::shared_ptr<basic::CollectionSyntaxTag> GetEndTags() { return endTags_; }

  inline const Branches& GetFinished() const { return finished_; }
  inline const Branches& GetResults() const { return results_; }
  inline Branch GetFather(Branch &branch);
  inline bool IsAnalysised() const;
  inline bool IsMainAnalysis() const;
  basic::SyntaxTag::Type::Val GetTheEndTag() const { return theEndTag_; }
  bool GetSucc() const { return succ_; }

  void Dump(JsonType &jsonType);

 private:
  std::shared_ptr<basic::NluContext> clause_;
  std::shared_ptr<basic::CollectionSyntaxTag> endTags_;
  std::string verifyStrategy_;
  bool traceEvent_;

  std::shared_ptr<AnalysisClauseBranch> master_;
  std::queue<std::shared_ptr<AnalysisClauseBranch>> branches_;
  Branches finished_;
  Branches results_;
  std::unordered_map<size_t, std::shared_ptr<AnalysisClauseBranch>> allBranches_;
  basic::SyntaxTag::Type::Val theEndTag_;
  bool succ_;
};

const std::shared_ptr<basic::NluContext>& AnalysisClause::GetClause() const {
  return clause_;
}

std::shared_ptr<basic::NluContext>& AnalysisClause::GetClause() {
  return clause_;
}

bool AnalysisClause::IsAnalysised() const {
  return results_.size() == 1;
}

bool AnalysisClause::IsMainAnalysis() const {
  return endTags_->IsStc();
}

}}}
