#pragma once

#include "../public.h"
#include "word_dict.h"
#include "gkb_zk.h"

namespace xforce { namespace nlu { namespace basic {

class Manager {
 public:
  bool Init();

  const WordDict& GetWordDict() const { return *wordDict_; }
  const GkbZk& GetGkbZk() const { return *gkbZk_; }

  inline static void SetWordDict(WordDict &wordDict);
  inline static void SetGkbZk(GkbZk &gkbZk);

  virtual ~Manager();

  static Manager& Get() { return *manager_; }
  static void Tini();

 private:
  WordDict *wordDict_;
  GkbZk *gkbZk_;

  static Manager *manager_;
};

void Manager::SetWordDict(WordDict &wordDict) {
  manager_->wordDict_ = &wordDict;
}

void Manager::SetGkbZk(GkbZk &gkbZk) {
  manager_->gkbZk_ = &gkbZk;
}

}}}
