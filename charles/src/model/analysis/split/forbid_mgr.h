#pragma once

#include "../public.h"
#include "forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

class Rule;

class ForbidMgr {
 private:
  typedef std::vector<ForbidItem> ForbidItems;

 private:
  static const size_t kCategoryGlobalRuleInterval = 100;

 public:
  ForbidMgr() {}
  virtual ~ForbidMgr();

  void AddRule(const Rule &rule);
  bool PreCheckRule(const Rule &rule);
  bool PostCheckRule(const Rule &rule);

  ForbidMgr* Clone() const;

 private:
  void AddForbidItem_(
          bool isLocal,
          size_t category,
          const ForbidItem &forbidItem);

 private:
  std::unordered_map<size_t, ForbidItems*> localForbidItems_;
  std::unordered_map<size_t, ForbidItems*> globalForbidItems_;
};

}}}
