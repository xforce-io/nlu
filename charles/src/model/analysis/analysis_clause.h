#pragma once

#include "public.h"
#include "analysis_component.h"

namespace xforce { namespace nlu { namespace charles {

class SplitRuleMgr;
class AnalysisClauseBranch;

class AnalysisClause : public AnalysisComponent {
 public:
  typedef std::list<std::shared_ptr<AnalysisClauseBranch>> Branches;

 public:
  AnalysisClause(
          const std::wstring &clause,
          basic::SyntaxTag::Type::Val endTag = basic::SyntaxTag::Type::kStc);

  virtual ~AnalysisClause();

  bool Init();
  bool Process();
  inline std::shared_ptr<basic::NluContext>& GetClause();
  inline const Branches& GetFinished() const { return finished_; }
  inline const Branches& GetResults() const { return results_; }
  inline bool IsAnalysised() const;
  void Dump(JsonType &jsonType);

 private:
  std::shared_ptr<basic::NluContext> clause_;
  basic::SyntaxTag::Type::Val endTag_;

  std::shared_ptr<AnalysisClauseBranch> master_;
  std::queue<std::shared_ptr<AnalysisClauseBranch>> branches_;
  Branches finished_;
  Branches results_;
};

std::shared_ptr<basic::NluContext>& AnalysisClause::GetClause() {
  return clause_;
}

bool AnalysisClause::IsAnalysised() const {
  return results_.size() == 1;
}

}}}
