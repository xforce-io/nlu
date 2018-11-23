#include "../clause.h"

#include "../base_modules.h"

namespace xforce { namespace nlu {

Clause::Clause() {
  featureSegment_ = new FeatureSegment();
}

void Clause::Segment() {
  BaseModules::Get().GetSegmentor().Parse(
      clause_, 
      featureSegment_->GetOffsets(), 
      featureNameEntity_->GetNameEntities());
}

Clause::~Clause() {
  XFC_DELETE(featureSegment_)
}

}}
