#include "../ner.h"
#include "../data/manager.h"
#include "../conf/conf.h"

namespace xforce { namespace nlu { namespace ner {

bool Ner::Init(const xforce::JsonType &confJson) {
  bool ret = Conf::Get().Init(confJson);
  if (!ret) {
    FATAL("fail_init_conf[ner]");
    return false;
  }

  ret = Manager::Get().Init();
  if (!ret) {
    FATAL("fail_init_data_manager[ner]");
    return false;
  }
  return true;
}

void Ner::Tini() {
  Manager::Tini();
  Conf::Tini();
}

}}}
