#include "../milkie.h"
#include "../conf/conf.h"
#include "../core/model/refer/refer_manager.h"
#include "../core/model/function/manager.h"

namespace xforce { namespace nlu { namespace milkie {

bool Milkie::Init(const std::string &confpath) {
  bool ret = Conf::Get().Init(confpath);
  if (!ret) {
    FATAL("fail_init_confpath[" << *StrHelper::Str2Wstr(confpath) << "]");
    return false;
  }

  ret = ReferManager::Get().BuildGlobalDict();
  if (!ret) {
    FATAL("fail_build_global_dict");
    return false;
  }

  auto manager = Manager::BuildGlobalManager();
  if (nullptr == manager) {
    FATAL("fail_build_global_manager");
    return false;
  }

  Manager::SetGlobalManager(manager);
  return true;
}

void Milkie::Tini() {
  Conf::Tini();
}

}}}
