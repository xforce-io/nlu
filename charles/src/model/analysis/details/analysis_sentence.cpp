#include "../analysis_sentence.h"

AnalysisSentence::AnalysisSentence(
    const std::wstring &sentence, 
    const std::vector<std::shared_ptr<AnalysisClause>> &analysisClauses) :
  sentence_(sentence),
  analysisClauses_(&analysisClauses) {}
