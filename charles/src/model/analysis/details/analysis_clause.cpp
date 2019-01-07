#include "../analysis_clause.h"

#include "../../base_modules.h"
#include "../../feature/feature_segments.h"
#include "../../feature/feature_name_entity.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(const std::wstring &clause) :
  clause_(clause) {}

void AnalysisClause::Segment() {
  basic::Segment::Vector segments;
  std::vector<std::shared_ptr<ner::NameEntity>> nameEntities;
  BaseModules::Get().GetSegmentor().Parse(clause_, segments, nameEntities);
  featureSegments_ = std::make_shared<FeatureSegments>(clause_, segments);
  for (auto iter = nameEntities.begin(); iter != nameEntities.end(); ++iter) {
    featureNameEntities_.push_back(std::make_shared<FeatureNameEntity>(*featureSegments_, *iter, 0));
  }
}

void AnalysisClause::Dump(JsonType &jsonType) {
  jsonType["clause"] = StrHelper::Wstr2Str(clause_);
  featureSegments_->Dump(jsonType["featureSegments"]);
  for (size_t i=0; i < featureNameEntities_.size(); ++i) {
    featureNameEntities_[i]->Dump(jsonType["featureNameEntities"][i]);
  }
}

}}}
