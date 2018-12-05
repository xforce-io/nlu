#include "../base_modules.h"
#include "segmentor/segmentor.h"

namespace xforce { namespace nlu { namespace charles {

BaseModules *BaseModules::baseModules_ = new BaseModules();

bool BaseModules::Init(const xforce::JsonType &conf) {
  segmentor_ = new xforce::nlu::segmentor::Segmentor();
  bool ret = segmentor_->Init(conf["segmentor"], conf["ner"]);
  if (!ret) {
    FATAL("fail_init_segmentor");
    return false;
  }
  return true;
}

}}}
