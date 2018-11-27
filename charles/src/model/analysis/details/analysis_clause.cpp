#include "../analysis_clause.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisClause::AnalysisClause(const std::wstring &clause) :
  clause_(clause) {}

void AnalysisClause::Segment() {
  std::vector<size_t> offsets;
  std::vector<std::shared_ptr<ner::NameEntity>> nameEntities;
  BaseModules::Get().GetSegmentor().Parse(clause_, offsets, nameEntities);
  featureSegments_ = std::make_shared<FeatureSegments>(offsets);
  for (auto iter = nameEntities.begin(); iter != nameEntities.end(); ++iter) {
    featureNameEntities_.push_back(std::make_shared<FeatureNameEntity>(*iter, 0));
  }
}

}}}
