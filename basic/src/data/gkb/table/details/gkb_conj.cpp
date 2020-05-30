#include "../gkb_conj.h"

namespace xforce { namespace nlu { namespace basic {

bool GkbConj::Init(
        const std::string &dir,
        const std::string &filepath) {
  if (!Super::Init(dir, filepath)) {
    return false;
  }
  return true;
}

bool GkbConj::Pos(
        const std::wstring &word,
        bool &prev,
        bool &mid,
        bool &post) {
  auto entries = GetEntries(word);
  if (nullptr == entries || entries->empty()) {
    return false;
  }

  prev = false;
  mid = false;
  post = false;
  for (size_t i=0; i < entries->size(); ++i) {
    if ((*entries)[i]->posPrev()) {
      prev = true;
    }

    if ((*entries)[i]->posMid()) {
      mid = true;
    }

    if ((*entries)[i]->posPost()) {
      post = true;
    }
  }
  return true;
}

}}}