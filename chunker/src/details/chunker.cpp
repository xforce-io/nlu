#include "../chunker.h"
#include "../conf/conf.h"

namespace xforce { namespace nlu { namespace chunker {

bool Chunker::Init(const xforce::JsonType &confJson) {
  bool ret = Conf::Get().Init(confJson);
  if (!ret) {
    FATAL("fail_init_conf[ner]");
    return false;
  }
  return true;
}

void Chunker::Tini() {
  Conf::Tini();
}

}}}
