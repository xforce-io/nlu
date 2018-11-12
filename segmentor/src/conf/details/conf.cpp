#include "../conf.h"

namespace xforce { namespace nlu { namespace segmentor {

Conf *Conf::conf_ = new Conf();

Conf::Conf() {}  

bool Conf::Init(const std::string &filepath) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf(filepath);

  XFC_FAIL_HANDLE_FATAL(
      NULL == conf || !conf->IsDict(), 
      "fail_init_service_conf[" << filepath << "]")

  XFC_FAIL_HANDLE_FATAL(
      !(*conf)["dataDir"].IsStr(),
      "fail_get_dataDir")  
  dataDir_ = (*conf)["dataDir"].AsStr();

  XFC_DELETE(conf)
  return true;

  ERROR_HANDLE:
  XFC_DELETE(conf)
  return false;
}

}}}
