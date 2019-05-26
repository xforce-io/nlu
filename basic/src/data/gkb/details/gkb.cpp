#include "../gkb.h"

namespace xforce { namespace nlu { namespace basic {

Gkb::Gkb()
  : gkbAdv_(nullptr) {}

Gkb::~Gkb() {
  XFC_DELETE(gkbAdv_)
}

bool Gkb::Init(const std::string &dir) {
  std::stringstream ss;
  ss << dir << "/gkb_global";

  gkbAdv_ = new GkbAdv();

  bool ret = gkbAdv_->Init(ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_adv");
    return false;
  }
  return true;
}


}}}