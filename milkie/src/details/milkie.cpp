#include "../milkie.h"
#include "../conf/conf.h"

namespace xforce { namespace nlu { namespace milkie {

bool Milkie::Init(const std::string &confpath) {
  bool ret = Conf::Init(confpath);
  if (!ret) {
    FATAL("fail_init_confpath[" << confpath << "]");
    return false;
  }

  ret = ReferManager::BuildGlobalDict();
  if (!ret) {
    FATAL("fail_build_global_dict");
    return false;
  }
  return true;
}

void Milkie::Tini() {
  Conf::Tini();
}

}}}