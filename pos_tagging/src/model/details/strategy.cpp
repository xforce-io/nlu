#include "../strategy.h"

namespace xforce { namespace nlu { namespace pos {

void Strategy::SetPos(
        basic::Segment &segment,
        basic::PosTag::Type::Val posTag,
        uint32_t strategy) {
  if (segment.GetTag() == basic::PosTag::Type::kUndef) {
    segment.SetTag(posTag);
    segment.SetStrategy(strategy);
  }
}

void Strategy::AddPos(
        basic::Segment &segment,
        basic::PosTag::Type::Val posTag) {
  segment.AddTag(posTag);
}

}}}
