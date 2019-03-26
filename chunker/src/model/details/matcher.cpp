#include "../matcher.h"

namespace xforce { namespace nlu { namespace chunker {

Matcher::Matcher() :
    milkie_(new milkie::Milkie()) {}

bool Matcher::Init() {
  bool ret = milkie_->Init("conf/milkie.conf");
  if (!ret) {
    FATAL("fail_init[milkie]");
    return false;
  }

  milkie_->GetManager().
  return true;
}

void Matcher::Match() {
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

}}}
