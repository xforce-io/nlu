#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace basic {

class WordDict;
class Gkb;

class Manager {
 public:
  bool Init();

  const WordDict& GetWordDict() const { return *wordDict_; }
  const Gkb& GetGkb() const { return *gkb_; }

  inline static void SetWordDict(WordDict &wordDict);
  inline static void SetGkb(Gkb &gkb);

  virtual ~Manager();

  static Manager& Get() { return *manager_; }
  static void Tini();

 private:
  WordDict *wordDict_;
  Gkb *gkb_;

  static Manager *manager_;
};

void Manager::SetWordDict(WordDict &wordDict) {
  manager_->wordDict_ = &wordDict;
}

void Manager::SetGkbZk(GkbZk &gkbZk) {
  manager_->gkbZk_ = &gkbZk;
}

}}}
