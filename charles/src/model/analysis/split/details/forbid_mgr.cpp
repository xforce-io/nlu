#include "../forbid_mgr.h"
#include "../forbid_item.h"
#include "../rule.h"

namespace xforce { namespace nlu { namespace charles {

ForbidMgr::~ForbidMgr() {
  for (auto &kv : forbidItems_) {
    delete kv.second;
  }
}

void ForbidMgr::AddRule(const Rule &rule) {
  ForbidItem forbidItem;
  if (!rule.GenForbid(forbidItem)) {
    return;
  }
  AddForbidItem_(rule.GetCategory(), forbidItem);
}

bool ForbidMgr::PreCheckRule(const Rule &rule) {
  auto iter = forbidItems_.find(rule.GetCategory());
  if (iter == forbidItems_.end()) {
    return true;
  }

  for (auto &item : *(iter->second)) {
    if (rule.PreCheckForbid(item)) {
      return false;
    }
  }
  return true;
}

bool ForbidMgr::PostCheckRule(const Rule &rule) {
  auto iter = forbidItems_.find(rule.GetCategory());
  if (iter == forbidItems_.end()) {
    return true;
  }

  for (auto &item : *(iter->second)) {
    if (rule.PostCheckForbid(item)) {
      return false;
    }
  }
  return true;
}

ForbidMgr* ForbidMgr::Clone() const {
  ForbidMgr *forbidMgr = new ForbidMgr();
  for (auto &kv : forbidItems_) {
    for (auto &item : *(kv.second)) {
      forbidMgr->AddForbidItem_(kv.first, item);
    }
  }
  return forbidMgr;
}

void ForbidMgr::AddForbidItem_(size_t category, const ForbidItem &forbidItem) {
  auto iter = forbidItems_.find(category);
  ForbidItems *forbidItems;
  if (iter != forbidItems_.end()) {
    forbidItems = iter->second;
  } else {
    forbidItems = new ForbidItems();
    forbidItems_.insert(std::make_pair(category, forbidItems));
  }
  forbidItems->push_back(forbidItem);
}

}}}
