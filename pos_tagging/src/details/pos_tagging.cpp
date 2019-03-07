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
    const std::vector<basic::DictItem*>* dictItems = basic::Manager::Get().GetWordDict().GetDictItems(word);
    if (dictItems != nullptr) {
      if (dictItems->size() == 1) {
        segment->SetPos(dictItems->at(0)->pos);
      }
    } else {
      auto wordStr = StrHelper::Wstr2Str(word);
      WARN("no_word_in_word_dict[" << *wordStr << "]");
    }

    basic::Manager::Get().GetGkbZk().GetPos()
  }

}

}}}
