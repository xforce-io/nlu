#include "../strategy.h"

namespace xforce { namespace nlu { namespace pos {

void Strategy::Process(basic::NluContext &nluContext) {
  nluContext_ = &nluContext;
}

void Strategy::SetPos(
        basic::Segment &segment,
        basic::PosTag::Type::Val posTag,
        uint32_t strategy) {
  if (segment.GetTag() == basic::PosTag::Type::kUndef) {
    segment.SetTag(
            basic::PosTag::EnhancePosTag(
                    posTag,
                    segment.GetQuery(nluContext_->GetQuery())));
    segment.SetStrategy(strategy);
  }
}

void Strategy::AddPos(
        basic::Segment &segment,
        basic::PosTag::Type::Val posTag) {
  segment.AddTag(posTag);
}

}}}
