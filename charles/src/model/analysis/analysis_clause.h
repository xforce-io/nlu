#pragma once

#include "public.h"
#include "analysis_component.h"
#include "analysis_clause_branch.h"
#include "nlu_context_split.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause : public AnalysisComponent {
 public:
  AnalysisClause(
          const std::wstring &clause);
  virtual ~AnalysisClause();

  bool Init();
  bool Process();
  void Dump(JsonType &jsonType);

 private:
  NluContextSplit *nluContextSplit_;

  std::shared_ptr<AnalysisClauseBranch> master_;
  std::queue<std::shared_ptr<AnalysisClauseBranch>> branches_;
  std::list<std::shared_ptr<AnalysisClauseBranch>> results_;
};

}}}
