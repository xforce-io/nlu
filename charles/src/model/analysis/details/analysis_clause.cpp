#include "../analysis_clause.h"

#include "../../base_modules.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(const std::wstring &clause) :
  father_(nullptr),
  clause_(clause),
  nluContext_(std::make_shared<std::wstring>(clause)) {}

void AnalysisClause::Segment() {
  BaseModules::Get().GetSegmentor().Parse(nluContext_);
  BaseModules::Get().GetPosTagging().Tagging(nluContext_);
}

void AnalysisClause::Dump(JsonType &jsonType) {
  jsonType["clause"] = *(StrHelper::Wstr2Str(clause_));
  //TODO : Add dump logic
}

}}}
