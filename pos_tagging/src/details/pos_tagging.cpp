#include "../pos_tagging.h"

namespace xforce { namespace nlu { namespace pos {

void PosTagging::Tagging(
    const std::wstring &clause,
    basic::FragmentSet<basic::Segment> &segments) {
  SetPosForWordWithUniqPos_(clause, segments);
}

void PosTagging::SetPosForWordWithUniqPos_(
    const std::wstring &clause,
    basic::FragmentSet<basic::Segment> &segments) {
  for (size_t i=0; i < segments.Size(); ++i) {
    auto &segment = segments[i];
    auto poses = basic::Manager::Get().GetGkbZk().GetPos(*(segment->GetStr()));
    if (poses->size() == 1) {
      segment->SetPos((*poses)[0]);
    }
  }
}

void PosTagging::SetPosCtbFromPos_(
      const std::wstring &clause,
      basic::FragmentSet<basic::Segment> &segments) {
  for (size_t i=0; i < segments.Size(); ++i) {
    auto &segment = segments[i];
    if (segment->GetPos() == basic::Pos::kN) {
      segment->SetPos
    }
  }
}

}}}
