#include "../analysis_clause.h"

#include "../../base_modules.h"
#include "../../feature/feature_segments.h"
#include "../../feature/feature_name_entity.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(const std::wstring &clause) :
  clause_(clause),
  featureSegments_(clause),
  featureNameEntities_(clause) {}

void AnalysisClause::Segment() {
  BaseModules::Get().GetSegmentor().Parse(clause_, featureSegments_, featureNameEntities_);
  pos::PosTagging::Tagging(clause_, fratureSegments_);
}

void AnalysisClause::Dump(JsonType &jsonType) {
  jsonType["clause"] = *(StrHelper::Wstr2Str(clause_));
  //TODO : Add dump logic
}

}}}
