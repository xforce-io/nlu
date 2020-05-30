#include "../strategy_complement.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyComplement::Process(basic::NluContext &nluContext) {
  Strategy::Process(nluContext);

  auto &clause = nluContext.GetQuery();
  typename basic::Segment::Set &segments = nluContext.Get<basic::Segment>();
  for (auto &segment : segments.GetAll()) {
    if (segment->GetTags().empty()) {
      auto segmentStr = segment->GetStrFromSentence(clause);
      auto poses = basic::Manager::Get().GetGkb().GetGkbGlobal().GetPosTags(segmentStr);
      if (poses != nullptr && poses->size() > 1) {
        SetPos(
                *segment,
                (*poses)[0],
                basic::Confidence::kFull,
                kStrategyOther);
        if ((*poses)[0] == basic::PosTag::Type::kV) {
          AddPos(*segment, basic::PosTag::Type::kVn);
        }

        for (size_t i=1; i < poses->size(); ++i) {
          AddPos(*segment, (*poses)[i]);
          if ((*poses)[i] == basic::PosTag::Type::kV) {
            AddPos(*segment, basic::PosTag::Type::kVn);
          }
        }
      }
    }
  }
}

}}}
