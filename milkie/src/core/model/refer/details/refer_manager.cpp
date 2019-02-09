#include "../refer_manager.h"
#include "../refer.h"
#include "../../../../conf/conf.h"

namespace xforce { namespace nlu { namespace milkie {

const std::wstring ReferManager::kGlobal = "_GLOBAL_";

ReferManager ReferManager::referManager_;

ReferManager::ReferManager() :
  globalDict_(nullptr) {}

ReferManager::~ReferManager() {
  XFC_DELETE(globalDict_)
}

bool ReferManager::BuildGlobalDict() {
  bool hasError = false;
  const std::vector<std::string> referFilepaths = Conf::Get().GetReferFilepaths();
  std::vector<std::string> lines;
  std::vector<std::wstring> wlines;
  for (auto &referFilepath : referFilepaths) {
    bool ret = IOHelper::ReadLinesFromFilepath(referFilepath, lines);
    if (!ret) {
      hasError = true;
      ERROR("fail_read_lines_from[" << referFilepath << "]");
      continue;
    }
  }

  for(auto &line : lines) {
    std::wstring wline;
    auto ret = StrHelper::Str2Wstr(line, wline);
    if (!ret) {
      hasError = true;
      ERROR("fail_convert_line[" << line << "]");
      continue;
    }
    wlines.push_back(wline);
  }

  if (nullptr == globalDict_) {
    globalDict_ = new Refer();
    for (auto &wline : wlines) {
      auto ret = globalDict_->Put(kGlobal, wline);
      if (!ret) {
        hasError = true;
        ERROR("fail_put_line[" << wline << "]");
        continue;
      }
    }
  } else {
    auto newDict = new Refer();
    for (auto &wline : wlines) {
      bool ret = newDict->Put(kGlobal, wline);
      if (!ret) {
        hasError = true;
        ERROR("fail_put_line[" << wline << "]");
        continue;
      }
    }
    globalDict_ = newDict;
  }
  return !hasError;
}

bool ReferManager::AddToGlobalDict(const std::string &filepath) {
  std::vector<std::string> lines;

  bool ret = IOHelper::ReadLinesFromFilepath(filepath, lines);
  if (!ret) {
    ERROR("fail_read_lines_from[" << filepath << "]");
    return false;
  }

  std::vector<std::wstring> wlines;
  for(auto &line : lines) {
    std::wstring wline;
    auto ret = StrHelper::Str2Wstr(line, wline);
    if (!ret) {
      ERROR("fail_convert_line[" << line << "]");
      continue;
    }
    wlines.push_back(wline);
  }

  for (auto &wline : wlines) {
    auto ret = globalDict_->Put(kGlobal, wline);
    if (!ret) {
      ERROR("fail_put_line[" << wline << "]");
      continue;
    }
  }
  return true;
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
