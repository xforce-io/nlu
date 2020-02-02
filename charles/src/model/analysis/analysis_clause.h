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
  inline std::shared_ptr<basic::NluContext>& GetClause();
  inline const Branches& GetFinished() const { return finished_; }
  inline const Branches& GetResults() const { return results_; }
  inline Branch GetFather(Branch &branch);
  inline bool IsAnalysised() const;
  inline bool IsMainAnalysis() const;

  void Dump(JsonType &jsonType);

 private:
  std::shared_ptr<basic::NluContext> clause_;
  basic::CollectionSyntaxTag endTags_;
  std::string verifyStrategy_;
  bool traceEvent_;

  std::shared_ptr<AnalysisClauseBranch> master_;
  std::queue<std::shared_ptr<AnalysisClauseBranch>> branches_;
  Branches finished_;
  Branches results_;
  std::unordered_map<size_t, std::shared_ptr<AnalysisClauseBranch>> allBranches_;
};

std::shared_ptr<basic::NluContext>& AnalysisClause::GetClause() {
  return clause_;
}

bool AnalysisClause::IsAnalysised() const {
  return results_.size() == 1;
}

bool AnalysisClause::IsMainAnalysis() const {
  return endTags_.IsStc();
}

}}}
