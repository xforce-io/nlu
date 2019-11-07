#include "../forbid_mgr.h"
#include "../forbid_item.h"
#include "../rule.h"

namespace xforce { namespace nlu { namespace charles {

ForbidMgr::~ForbidMgr() {
  for (auto &kv : localForbidItems_) {
    delete kv.second;
  }
}

void ForbidMgr::AddRule(const Rule &rule) {
  //gen forbid item for local category
  std::vector<ForbidItem> forbidItems;
  rule.GenForbid(forbidItems);
  for (auto &forbidItem : forbidItems) {
    AddForbidItem_(true, rule.GetCategory(), forbidItem);
  }

  //gen forbid item for global category
  forbidItems.clear();
  rule.GenGlobalForbid(forbidItems);
  for (auto &forbidItem : forbidItems) {
    AddForbidItem_(false, forbidItem.GetCategoryRule(), forbidItem);
  }
}

bool ForbidMgr::GlobalCheckRule(const Rule &rule) {
  for (auto kv : globalForbidItems_) {
    for (auto &item : *(kv.second)) {
      if (rule.GlobalCheckForbid(item)) {
        return false;
      }
    }
  }
  return true;
}

bool ForbidMgr::PreCheckRule(const Rule &rule) {
  auto iter = localForbidItems_.find(rule.GetCategory());
  if (iter != localForbidItems_.end()) {
    for (auto &item : *(iter->second)) {
      if (rule.PreCheckForbid(item)) {
        return false;
      }
    }
  }
  return true;
}

bool ForbidMgr::PostCheckRule(const Rule &rule) {
  auto iter = localForbidItems_.find(rule.GetCategory());
  if (iter == localForbidItems_.end()) {
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
  auto forbidMgr = new ForbidMgr();
  for (auto &kv : localForbidItems_) {
    for (auto &item : *(kv.second)) {
      forbidMgr->AddForbidItem_(true, kv.first, item);
    }
  }

  for (auto &kv : globalForbidItems_) {
    for (auto &item : *(kv.second)) {
      forbidMgr->AddForbidItem_(false, kv.first, item);
    }
  }
  return forbidMgr;
}

void ForbidMgr::AddForbidItem_(
        bool isLocal,
        size_t category,
        const ForbidItem &forbidItem) {
  std::unordered_map<size_t, ForbidItems*> *forbidItemsMap = nullptr;
  if (isLocal) {
    forbidItemsMap = &localForbidItems_;
  } else {
    forbidItemsMap = &globalForbidItems_;
  }

  auto iter = forbidItemsMap->find(category);
  ForbidItems *forbidItems;
  if (iter != forbidItemsMap->end()) {
    forbidItems = iter->second;
  } else {
    forbidItems = new ForbidItems();
    forbidItemsMap->insert(std::make_pair(category, forbidItems));
  }
  forbidItems->push_back(forbidItem);
}

}}}
