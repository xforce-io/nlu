#include "../milkie.h"
#include "../conf/conf.h"
#include "../core/model/refer/refer_manager.h"

namespace xforce { namespace nlu { namespace milkie {

bool Milkie::Init(const std::string &confpath) {
  bool ret = Conf::Get().Init(confpath);
  if (!ret) {
    std::wstring wConfpath;
    StrHelper::Str2Wstr(confpath, wConfpath);
    FATAL("fail_init_confpath[" << wConfpath << "]");
    return false;
  }

  ret = ReferManager::Get().BuildGlobalDict();
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
