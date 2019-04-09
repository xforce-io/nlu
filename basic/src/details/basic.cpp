#include "../basic.h"
#include "../conf/conf.h"
#include "../data/manager.h"

namespace xforce { namespace nlu { namespace basic {

bool Basic::Init(const xforce::JsonType &confPos) {
  bool ret = Conf::Get().Init(confPos["basic"]);
  if (!ret) {
    FATAL("fail_init_basic_conf")
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
