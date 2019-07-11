#pragma once

#include "public.h"
#include "analysis_component.h"
#include "analysis_clause_branch.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause : public AnalysisComponent {
 public:
  AnalysisClause(
          const std::wstring &clause);

 private:
  std::shared_ptr<AnalysisClauseBranch> master_;
  std::queue<AnalysisClauseBranch> branches_;
};

}}}
