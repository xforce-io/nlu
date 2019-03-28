#include "../conf.h"

namespace xforce { namespace nlu { namespace charles {

Conf *Conf::conf_ = new Conf();

Conf::Conf() {}  

bool Conf::Init(const xforce::JsonType &confJson) {
  if (!confJson["dataDir"].IsStr()) {
    FATAL("fail_get_dataDir");
    return false;
  }
  dataDir_ = confJson["dataDir"].AsStr();
  return true;
}

void Conf::Tini() {
  XFC_DELETE(conf_)
}

}}}
