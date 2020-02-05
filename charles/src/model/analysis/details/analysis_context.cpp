#include "../analysis_context.h"
#include "../analysis_clause.h"
#include "../analysis_sentence.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisContext::AnalysisContext(const std::wstring &query) {
  std::vector<std::wstring> vals;
  std::wstring seps = L",，。.";
  StrHelper::SplitStr(query, seps, vals);
  for (auto val : vals) {
    analysisClauses_.push_back(std::make_shared<AnalysisClause>(
            val,
            basic::CollectionSyntaxTag(true)));
  }

  analysisSentence_ = std::make_shared<AnalysisSentence>(query, analysisClauses_);
}

void AnalysisContext::Dump(JsonType &jsonType) {
  analysisSentence_->Dump(jsonType["analysisSentence"]);
  for (size_t i=0; i < analysisClauses_.size(); ++i) {
    analysisClauses_[i]->Dump(jsonType["analysisClauses"][i]);
  }
}

}}}
