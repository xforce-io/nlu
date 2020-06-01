#include "../conf.h"

namespace xforce { namespace nlu { namespace semantic {

Conf *Conf::conf_ = new Conf();

Conf::Conf() {}

bool Conf::Init(const xforce::JsonType &confJson) {
  XFC_FAIL_HANDLE_FATAL(
          !confJson["dataDir"].IsStr(),
          "fail_get_dataDir")
  dataDir_ = confJson["dataDir"].AsStr();

  XFC_FAIL_HANDLE_FATAL(
          !confJson["parserConfpath"].IsStr(),
          "fail_get_parserConfpath")
  parserConfpath_ = confJson["parserConfpath"].AsStr();

  return true;

  ERROR_HANDLE:
  return false;
}

void Conf::Tini() {
  XFC_DELETE(conf_)
}

}}}
