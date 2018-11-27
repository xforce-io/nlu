#include "../runtime.h"

namespace xforce { namespace nlu { namespace charles {

Runtime::Runtime() :
  currentAnalysisContext_(NULL) {}

Runtime::~Runtime() {
  XFC_DELETE(currentAnalysisContext_)
}

bool Runtime::Process(const std::wstring &query) {
  currentAnalysisContext_ = new AnalysisContext();
  bool ret = currentAnalysisContext_->Init(query);
  if (!ret) {
    return false;
  }
  return true;
}

bool Runtime::Round_() {
  AnalysisContext::AnalysisClauses analysisClauses = currentAnalysisContext_->GetAnalysisClauses();
  bool modified = false;
  for (auto analysisClausePtr : analysisClauses) {
    if (ProcessorContext::Get().ProcessClause(
        *currentAnalysisContext_, 
        *analysisClausesPtr)) {
      modified = true;
    }
  }

  if (ProcessorContext::Get().ProcessorSentence(
      *currentAnalysisContext_, 
      currentAnalysisContext_->GetAnalysisSentence())) {
    modified = true;
  }
  return modified;
}

}}}
