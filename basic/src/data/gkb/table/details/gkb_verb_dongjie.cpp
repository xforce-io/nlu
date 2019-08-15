#include "../gkb_verb_dongjie.h"

namespace xforce { namespace nlu { namespace basic {

bool GkbVerbDongjie::IsPhrase(
        const std::wstring &word0,
        const std::wstring &word1) const {
  const std::vector<const EntryVerbDongjie*> *entries = GetEntries(word0);
  if (nullptr == entries) {
    return false;
  }

  for (auto *entry : *entries) {
    if (entry->ConnWord(word1)) {
      return true;
    }
  }
  return false;
}

}}}
