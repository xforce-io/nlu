#include "../strategy.h"

namespace xforce { namespace nlu { namespace pos {

void Strategy::Process(basic::NluContext &nluContext) {
  nluContext_ = &nluContext;
}

void Strategy::SetPos(
        basic::Segment &segment,
        basic::PosTag::Type::Val posTag,
        basic::Confidence confidence,
        uint32_t strategy) {
  if (segment.GetTag() == basic::PosTag::Type::kUndef ||
      confidence.Gt(confidence)) {
    segment.SetTag(
            basic::PosTag::EnhancePosTag(
                    posTag,
                    segment.GetQuery(nluContext_->GetQuery())));
    segment.SetConfidence(confidence);
    segment.SetStrategy(strategy);
  }
}

void Strategy::AddPos(
        basic::Segment &segment,
        basic::PosTag::Type::Val posTag) {
  segment.AddTag(posTag);
}

}}}
