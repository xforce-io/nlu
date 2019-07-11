#include <segmentor/segmentor.h>
#include "../analysis_clause_branch.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClauseBranch::AnalysisClauseBranch(const std::wstring &clause) :
  nluContext_(std::make_shared<basic::NluContext>(clause)) {}

AnalysisClauseBranch::AnalysisClauseBranch(const basic::NluContext &nluContext) :
  nluContext_(nluContext.Clone()) {}

bool AnalysisClauseBranch::Process(
        std::queue<std::shared_ptr<AnalysisClauseBranch>> &children) {

}

std::shared_ptr<AnalysisClauseBranch> Clone() {

}

}}}
