#include "../runtime.h"
#include "../analysis/analysis_context.h"
#include "../process/processor_context.h"

namespace xforce { namespace nlu { namespace charles {

Runtime::Runtime() :
  currentAnalysisContext_(nullptr) {}

Runtime::~Runtime() {
  XFC_DELETE(currentAnalysisContext_)
}

bool Runtime::Process(const std::wstring &query) {
  currentAnalysisContext_ = new AnalysisContext(query);
  while (Round_()) {
  }
  return true;
}

void Runtime::DumpAnalysisContext(JsonType &jsonType) {
  currentAnalysisContext_->Dump(jsonType);
}

bool Runtime::Round_() {
  AnalysisContext::AnalysisClauses analysisClauses = currentAnalysisContext_->GetAnalysisClauses();
  bool modified = false;
  for (auto analysisClausePtr : analysisClauses) {
    if (ProcessorContext::Get().ProcessClause(
        *currentAnalysisContext_, 
        *analysisClausePtr)) {
      modified = true;
    }
  }

  if (ProcessorContext::Get().ProcessSentence(
      *currentAnalysisContext_, 
      currentAnalysisContext_->GetAnalysisSentence())) {
    modified = true;
  }
  return modified;
}

}}}
