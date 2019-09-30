#include "../gkb_verb.h"

namespace xforce { namespace nlu { namespace basic {

bool GkbVerb::Init(
        const std::string &dir,
        const std::string &filepath) {
  if (!Super::Init(dir, filepath)) {
    return false;
  }

  for (auto *entry : entries_) {
    if (entry->IsDongjie()) {
      dongjie_.insert(entry->GetWord());
    }

    if (entry->IsDongqu()) {
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
  return gkbVerbDongjie_->IsPhrase(word0, word1) ||
      gkbVerbDongqu_->IsPhrase(word0, word1);
}

bool GkbVerb::IsZhu(const std::wstring &word) const {
  auto entries = GetEntries(word);
  if (nullptr == entries || entries->empty()) {
    return false;
  }

  for (auto *entry : *entries) {
    if (entry->IsZhu()) {
      return true;
    }
  }
  return false;
}

bool GkbVerb::TiWeiZhun(
    const std::wstring &word,
    bool &isArgTi,
    bool &isArgWei,
    bool &isArgZhun) const {
  auto entries = GetEntries(word);
  if (nullptr == entries || entries->empty()) {
    return false;
  }

  isArgTi = false;
  isArgWei = false;
  isArgZhun = false;
  for (size_t i=0; i < entries->size(); ++i) {
    if ((*entries)[i]->IsArgTi()) {
      isArgTi = true;
    }

    if ((*entries)[i]->IsArgWei()) {
      isArgWei = true;
    }

    if ((*entries)[i]->IsArgZhun()) {
      isArgZhun = true;
    }
  }
  return true;
}

}}}
