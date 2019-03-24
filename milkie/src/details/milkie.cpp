#include "../milkie.h"
#include "../conf/conf.h"
#include "../core/model/refer/refer_manager.h"
#include "../manager/manager.h"

namespace xforce { namespace nlu { namespace milkie {

Milkie::Milkie() :
    conf_(new Conf()),
    referManager_(new ReferManager()),
    manager_(new Manager()) {}

bool Milkie::Init(const std::string &confpath) {
  bool ret = conf_->Init(confpath);
  if (!ret) {
    FATAL("fail_init_confpath[" << *StrHelper::Str2Wstr(confpath) << "]");
    return false;
  }

  ret = referManager_->BuildGlobalDict(*conf_);
  if (!ret) {
    FATAL("fail_build_global_dict");
    return false;
  }

  ret = manager_->Init(conf_->GetReferFilepaths());
  if (!ret) {
    FATAL("fail_build_global_manager");
    return false;
  }
  return true;
}

Milkie::~Milkie() {
  XFC_DELETE(manager_)
  XFC_DELETE(referManager_)
  XFC_DELETE(conf_)
}

}}}
