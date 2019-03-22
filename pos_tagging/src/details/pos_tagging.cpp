#include "../pos_tagging.h"

namespace xforce { namespace nlu { namespace pos {

void PosTagging::Tagging(
    const std::wstring &clause,
    basic::FragmentSet<basic::Segment> &segments) {
  SetPosForWordWithUniqPos_(clause, segments);
  SetPosCtbFromPos_(clause, segments);
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
    auto pos = segment->GetPos();
    if (basic::Pos::kN == pos) {
      segment->SetPosCtb(basic::PosCtb::kNn);
    } else if (basic::Pos::kT == pos) {
      segment->SetPosCtb(basic::PosCtb::kNt);
    } else if (basic::Pos::kS == pos ||
        basic::Pos::kF == pos) {
      segment->SetPosCtb(basic::PosCtb::kLc);
    } else if (basic::Pos::kM == pos) {
      segment->SetPosCtb(basic::PosCtb::kCd);
    } else if (basic::Pos::kQ == pos) {
      segment->SetPosCtb(basic::PosCtb::kM);
    } else if (basic::Pos::kR == pos) {
      segment->SetPosCtb(basic::PosCtb::kPn);
    } else if (basic::Pos::kV == pos) {
      segment->SetPosCtb(basic::PosCtb::kVv);
    } else if (basic::Pos::kA == pos) {
      segment->SetPosCtb(basic::PosCtb::kJj);
    } else if (basic::Pos::kB == pos) {
      segment->SetPosCtb(basic::PosCtb::kJj);
    } else if (basic::Pos::kD == pos) {
      segment->SetPosCtb(basic::PosCtb::kAd);
    } else if (basic::Pos::kP == pos) {
      segment->SetPosCtb(basic::PosCtb::kP);
    } else if (basic::Pos::kC == pos) {
      segment->SetPosCtb(basic::PosCtb::kCc);
    } else if (basic::Pos::kW == pos) {
      segment->SetPosCtb(basic::PosCtb::kPu);
    }
  }
}

}}}
