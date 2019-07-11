#include "../processor_clause.h"

#include "../../analysis/analysis_context.h"
#include "../../analysis/analysis_clause.h"

#include "../../base_modules.h"

namespace xforce { namespace nlu { namespace charles {

bool ProcessorClause::Process(
        AnalysisContext &analysisContext,
        AnalysisClause &analysisClause) {
  std::queue<std::shared_ptr<AnalysisClause>> analysises;
  if (analysisClause.Process(analysises)) {
    return true;
  }

  while (analysises.empty()) {
    if (analysisClause.Process(analysises)) {
      return true;
    }
  }
}

}}}
