#include "../conf.h"

namespace xforce { namespace nlu { namespace pos {

Conf *Conf::conf_ = new Conf();

Conf::Conf() {}  

bool Conf::Init(const xforce::JsonType &confJson) {
  XFC_FAIL_HANDLE_FATAL(
      !confJson["dataDir"].IsStr(),
      "fail_get_dataDir")  
  dataDir_ = confJson["dataDir"].AsStr();
  return true;

  ERROR_HANDLE:
  return false;
}

void Conf::Tini() {
  XFC_DELETE(conf_)
}

}}}
