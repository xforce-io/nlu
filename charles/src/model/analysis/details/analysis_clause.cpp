#include "../analysis_clause.h"

#include "../../base_modules.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(
        const std::wstring &clause) :
  isMaster_(false),
  nluContext_(std::make_shared<basic::NluContext>(clause)) {}

AnalysisClause::AnalysisClause(
        const std::wstring &clause,
        bool isMaster) :
  isMaster_(isMaster),
  nluContext_(std::make_shared<basic::NluContext>(clause)) {}

void AnalysisClause::Process() {
  BaseModules::Get().GetSegmentor().Parse(nluContext_);
  ancestors_.insert(std::make_pair(kSegment, Clone()));

  BaseModules::Get().GetPosTagging().Tagging(nluContext_);
  ancestors_.insert(std::make_pair(kPosTag, Clone()));

}

std::shared_ptr<AnalysisClause> AnalysisClause::Clone() {
  auto cloned = std::make_shared<AnalysisClause>(
          nluContext_->GetQuery(),
          false);
  cloned->nluContext_ = nluContext_->Clone();
  return cloned;
}

void AnalysisClause::Dump(JsonType &jsonType) {
  jsonType["clause"] = *(StrHelper::Wstr2Str(nluContext_->GetQuery()));
  //TODO : Add dump logic
}

}}}
