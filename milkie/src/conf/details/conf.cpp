#include "../conf.h"

namespace xforce { namespace nlu { namespace milkie {

Conf *Conf::conf_ = new Conf();

Conf::Conf() {}  

bool Conf::Init(const xforce::JsonType &confJson) {
  XFC_FAIL_HANDLE_FATAL(
      !confJson["debugMode"].IsStr(),
      "fail_get_debug_mode")
  dataDir_ = confJson["debugMode"].AsStr();
  return true;

  ERROR_HANDLE:
  return false;
}

void Conf::Tini() {
  XFC_DELETE(conf_)
}

}}}
