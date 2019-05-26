#include "../gkb.h"
#include "../table/gkb_global.h"

namespace xforce { namespace nlu { namespace basic {

Gkb::Gkb() :
  gkbGlobal_(nullptr),
  gkbAdv_(nullptr) {}

Gkb::~Gkb() {
  XFC_DELETE(gkbAdv_)
  XFC_DELETE(gkbGlobal_)
}

bool Gkb::Init(const std::string &dir) {
  std::stringstream ss;
  ss << dir << "/gkb_global";
  gkbGlobal_ = new GkbGlobal();
  bool ret = gkbGlobal_->Init(ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_global");
    return false;
  }

  ss.str("");
  ss << dir << "/gkb_adv";
  gkbAdv_ = new GkbAdv();
  ret = gkbAdv_->Init(ss.str());
  if (!ret) {
    FATAL("fail_init_gkb_adv");
    return false;
  }
  return true;
}


}}}