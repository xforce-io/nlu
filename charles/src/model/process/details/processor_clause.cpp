#include "../processor_clause.h"

#include "../../analysis/analysis_context.h"
#include "../../analysis/analysis_clause.h"

#include "../../base_modules.h"

namespace xforce { namespace nlu { namespace charles {

bool ProcessorClause::Process(
        AnalysisContext &analysisContext,
        AnalysisClause &analysisClause) {
  return analysisClause.Process();
}

}}}
