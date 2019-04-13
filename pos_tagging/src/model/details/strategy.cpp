#include "../strategy.h"

namespace xforce { namespace nlu { namespace pos {

void Strategy::SetPos(
        std::shared_ptr<basic::Segment> &segment,
        basic::PosTag::Type posTag,
        uint32_t strategy) {
  if (segment->GetPosTag() != basic::PosTag::kUndef) {
    segment->SetPosTag(posTag);
    segment->SetStrategy(strategy);
  }
}

}}}
