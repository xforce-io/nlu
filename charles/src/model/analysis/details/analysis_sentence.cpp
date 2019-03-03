#include "../analysis_sentence.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisSentence::AnalysisSentence(
    const std::wstring &sentence, 
    const std::vector<std::shared_ptr<AnalysisClause>> &analysisClauses) :
  sentence_(sentence),
  analysisClauses_(&analysisClauses) {}

void AnalysisSentence::Dump(JsonType &jsonType) {
  jsonType["sentence"] = *(StrHelper::Wstr2Str(sentence_));
}

}}}
