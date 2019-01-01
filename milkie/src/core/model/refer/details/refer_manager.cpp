#include "../refer_manager.h"
#include "../refer.h"

namespace xforce { namespace nlu { namespace milkie {

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
