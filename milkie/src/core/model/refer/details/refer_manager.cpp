#include "../refer_manager.h"
#include "../refer.h"
#include "../../../../conf/conf.h"

namespace xforce { namespace nlu { namespace milkie {

ReferManager ReferManager::referManager_;

ReferManager::ReferManager() :
  globalDict_(nullptr) {}

ReferManager::~ReferManager() {
  XFC_DELETE(globalDict_)
}

void ReferManager::BuildGlobalDict() {
  const std::string& referFilepath = Conf::Get().GetReferFilepath();
  if (nullptr == globalDict_) {
    globalDict_ = new Refer();

  } else {

  }
}

bool ReferManager::PutLocalRefer(
    const std::wstring &blockKey, 
    const std::wstring &line) {
  std::shared_ptr<Refer> localRefer;
  auto iter = localDict_.find(blockKey);
  if (iter != localDict_.end()) {
    localRefer = iter->second; 
  } else {
    localRefer = std::make_shared<Refer>();
    localDict_.insert(std::make_pair(blockKey, localRefer));
  }
  return localRefer->Put(blockKey, line);
}

std::shared_ptr<PatternExpr> ReferManager::Get(
    const std::wstring &blockKey, 
    const std::wstring &key) {
  auto iter = localDict_.find(blockKey);
  if (iter != localDict_.end()) {
    return iter->second->Get(key);
  } else {
    return nullptr;
  }
}

}}}
