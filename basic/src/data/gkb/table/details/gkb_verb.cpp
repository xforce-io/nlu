#include "../gkb_verb.h"

namespace xforce { namespace nlu { namespace basic {

bool GkbVerb::Init(
        const std::string &dir,
        const std::string &filepath) {
  if (!Super::Init(dir, filepath)) {
    return false;
  }

  for (auto *entry : entries_) {
    if (entry->isDongjie()) {
      dongjie_.insert(entry->GetWord());
    }

    if (entry->isDongqu()) {
      dongqu_.insert(entry->GetWord());
    }
  }

  std::stringstream ss;
  ss << dir << "/gkb_verb_dongjie";
  gkbVerbDongjie_ = new GkbVerbDongjie();
  bool ret = gkbVerbDongjie_->Init(dir, ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_verb_dongjie");
    return false;
  }

  ss.str("");
  ss << dir << "/gkb_verb_dongqu";
  gkbVerbDongqu_ = new GkbVerbDongqu();
  ret = gkbVerbDongqu_->Init(dir, ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_verb_dongqu");
    return false;
  }
  return true;
}

bool GkbVerb::IsDongjieOrDongquPhrase(
    const std::wstring &word0,
    const std::wstring &word1) const {
  return gkbVerbDongqu_->IsPhrase(word0, word1);
}

EntryVerb::TiWeiZhun::Val GkbVerb::TiWeiZhun(
    const std::wstring &word) const {
  auto entries = GetEntries(word);
  if (nullptr == entries || entries->empty()) {
    return EntryVerb::TiWeiZhun::kOther;
  }

  EntryVerb::TiWeiZhun::Val firstTag = (*entries)[0]->TiWeiZhun();
  for (size_t i=1; i < entries->size(); ++i) {
    if ((*entries)[i]->TiWeiZhun() != firstTag) {
      return EntryVerb::TiWeiZhun::kOther;
    }
  }
  return firstTag;
}

}}}
