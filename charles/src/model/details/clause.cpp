#include "../clause.h"
#include "../base_modules.h"

namespace xforce { namespace nlu { namespace charles {

Clause::Clause(const std::wstring &clause) :
  clause_(clause),
  featureSegments_(NULL) {}

void Clause::Segment() {
  basic::Segment::Vector segments;
  std::vector<std::shared_ptr<ner::NameEntity>> nameEntities;
  BaseModules::Get().GetSegmentor().Parse(clause_, segments, nameEntities);

  featureSegments_ = new FeatureSegments(clause_, segments);
  for (auto iter = nameEntities.begin(); iter != nameEntities.end(); ++iter) {
    featureNameEntities_.push_back(new FeatureNameEntity(*featureSegments_, *iter, 0));
  }
}

Clause::~Clause() {
  for (auto iter = featureNameEntities_.begin(); iter != featureNameEntities_.end(); ++iter) {
    XFC_DELETE(*iter)
  }
  XFC_DELETE(featureSegments_)
}

}}}
