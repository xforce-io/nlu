#include "../gkb.h"
#include "../table/gkb_global.h"

namespace xforce { namespace nlu { namespace basic {

Gkb::Gkb() :
  gkbGlobal_(nullptr),
  gkbVerb_(nullptr),
  gkbAdv_(nullptr) {}

Gkb::~Gkb() {
  XFC_DELETE(gkbAdv_)
  XFC_DELETE(gkbVerb_)
  XFC_DELETE(gkbGlobal_)
}

bool Gkb::Init(const std::string &dir) {
  std::stringstream ss;
  ss << dir << "/gkb_global";
  gkbGlobal_ = new GkbGlobal();
  bool ret = gkbGlobal_->Init(dir, ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_global");
    return false;
  }

  ss.str("");
  ss << dir << "/gkb_verb";
  gkbVerb_ = new GkbVerb();
  ret = gkbVerb_->Init(dir, ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_verb");
    return false;
  }

  ss.str("");
  ss << dir << "/gkb_adv";
  gkbAdv_ = new GkbAdv();
  ret = gkbAdv_->Init(dir, ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_adv");
    return false;
  }
  return true;
}

bool Gkb::IsPhrase(const std::wstring &word0, const std::wstring &word1) const {
  return gkbGlobal_->IsPhrase(word0, word1) ||
      gkbVerb_->IsPhrase(word0, word1) ||
      gkbAdv_->IsPhrase(word0, word1);
}

}}}