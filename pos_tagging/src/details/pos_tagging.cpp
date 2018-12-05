#include "../pos_tagging.h"

namespace xforce { namespace nlu { namespace pos {

void PosTagging::Tagging(
    const std::wstring &clause,
    basic::Segments &segments) {
  for (size_t i=0; i < segments.size(); ++i) {
    basic::Segment &segment = segments[i];
    std::wstring word = clause.substr(
        segment.GetOffset(), 
        segment.GetLen());
    const std::vector<basic::DictItem*>* dictItems = basic::Manager::Get().GetWordDict().GetDictItems(word);
    if (NULL != dictItems) {
      if (dictItems->size() == 1) {
        segment.SetPos(dictItems->at(0)->pos);
      }
    } else {
      std::string wordStr;
      StrHelper::Wstr2Str(word, wordStr);
      WARN("no_word_in_word_dict[" << wordStr << "]");
    }
  }
}

}}}
