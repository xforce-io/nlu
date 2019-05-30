#include "../strategy.h"

namespace xforce { namespace nlu { namespace pos {

void Strategy::SetPos(
        std::shared_ptr<basic::Segment> &segment,
        basic::PosTag::Type::Val posTag,
        uint32_t strategy) {
  if (segment->GetPosTag() == basic::PosTag::Type::kUndef) {
    segment->SetPosTag(posTag);
    segment->SetStrategy(strategy);
  }
}

void Strategy::AddPos(
        std::shared_ptr<basic::Segment> &segment,
        basic::PosTag::Type::Val posTag) {
  segment->AddPosTag(posTag);
}

}}}
