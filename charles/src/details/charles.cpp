#include "../charles.h"
#include "../conf/conf.h"
#include "../model/base_modules.h"

namespace xforce { namespace nlu { namespace charles {

Charles Charles::charles_;

Charles::Charles() {}

Charles::~Charles() {
}

bool Charles::Init() {
  return true;
}

void Charles::Process(std::shared_ptr<basic::NluContext> nluContext) {
}

bool Charles::Init(const xforce::JsonType &confJson) {
  bool ret = BaseModules::Init(confJson);
  if (!ret) {
    FATAL("fail_init_conf[base_module]");
    return false;
  }

  ret = Conf::Get().Init(confJson["charles"]);
  if (!ret) {
    FATAL("fail_init_conf[charles]");
    return false;
  }

  ret = charles_.Init();
  if (!ret) {
    FATAL("fail_init_charles");
    return false;
  }
  return true;
}

void Charles::Parse(std::shared_ptr<basic::NluContext> nluContext) {
  return charles_.Process(nluContext);
}

}}}
