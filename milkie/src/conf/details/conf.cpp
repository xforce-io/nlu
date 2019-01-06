#include "../conf.h"

namespace xforce { namespace nlu { namespace milkie {

Conf *Conf::conf_ = new Conf();

Conf::Conf() {}  

bool Conf::Init(const xforce::JsonType &confJson) {
  XFC_FAIL_HANDLE_FATAL(
      !confJson["debugMode"].IsStr(),
      "fail_get_debug_mode")
  debugMode_ = confJson["debugMode"].AsBool();
  return true;

  ERROR_HANDLE:
  return false;
}

void Conf::Tini() {
  XFC_DELETE(conf_)
}

}}}
