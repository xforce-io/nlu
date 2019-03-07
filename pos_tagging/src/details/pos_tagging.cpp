#include "../pos_tagging.h"

namespace xforce { namespace nlu { namespace pos {

void PosTagging::Tagging(
    const std::wstring &clause,
    basic::FragmentSet<basic::Segment> &segments) {
  for (size_t i=0; i < segments.Size(); ++i) {
    auto &segment = segments[i];
    std::wstring word = clause.substr(
        segment->GetOffset(),
        segment->GetLen());

    auto poses = basic::Manager::Get().GetGkbZk().GetPos(word);
    if (poses->size() == 1) {
      segment->SetPos((*poses)[0]);
    }
  }
}

}}}
