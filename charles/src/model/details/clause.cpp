#include "../clause.h"
#include "../base_modules.h"
#include "../feature/feature_segments.h"
#include "../feature/feature_name_entity.h"

namespace xforce { namespace nlu { namespace charles {

Clause::Clause(const std::wstring &clause) :
  clause_(clause),
  featureSegments_(NULL) {}

void Clause::Segment() {
  std::vector<size_t> offsets;
  std::vector<std::shared_ptr<ner::NameEntity>> nameEntities;
  BaseModules::Get().GetSegmentor().Parse(clause_, offsets, nameEntities);

  featureSegments_ = new FeatureSegments(offsets);
  for (auto iter = nameEntities.begin(); iter != nameEntities.end(); ++iter) {
    featureNameEntities_.push_back(new FeatureNameEntity(*iter, 0));
  }
}

Clause::~Clause() {
  for (auto iter = featureNameEntities_.begin(); iter != featureNameEntities_.end(); ++iter) {
    XFC_DELETE(*iter)
  }
  XFC_DELETE(featureSegments_)
}

}}}
