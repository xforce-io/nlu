#include "../gkb_verb.h"

namespace xforce { namespace nlu { namespace basic {

bool GkbVerb::Init(
        const std::string &dir,
        const std::string &filepath) {
  if (!Super::Init(dir, filepath)) {
    return false;
  }

  std::stringstream ss;
  ss << dir << "/gkb_verb_dongqu";
  gkbVerbDongqu_ = new GkbVerbDongqu();
  bool ret = gkbVerbDongqu_->Init(dir, ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_verb_dongqu");
    return false;
  }
  return true;
}

bool GkbVerb::IsPhrase(
    const std::wstring &word0,
    const std::wstring &word1) const {
  return gkbVerbDongqu_->IsPhrase(word0, word1);
}

}}}
