#include "../basic.h"
#include "../conf/conf.h"
#include "../data/manager.h"

namespace xforce { namespace nlu { namespace basic {

bool Basic::Init(const xforce::JsonType &confBasic) {
  bool ret = Conf::Get().Init(confBasic);
  if (!ret) {
    FATAL("fail_init_basic_conf");
    return false;
  }

  ret = Manager::Get().Init();
  if (!ret) {
    FATAL("fail_init_basic_manager");
    return false;
  }
  return true;
}

}}}
