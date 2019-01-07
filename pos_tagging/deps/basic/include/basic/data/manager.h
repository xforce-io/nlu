#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace basic {

class WordDict;  

class Manager {
 public:
  bool Init();

  const WordDict& GetWordDict() const { return *wordDict_; }

  inline static void SetWordDict(WordDict &wordDict);

  virtual ~Manager();

  static Manager& Get() { return *manager_; }
  static void Tini();

 private:
  WordDict *wordDict_;

  static Manager *manager_;
};

void Manager::SetWordDict(WordDict &wordDict) {
  manager_->wordDict_ = &wordDict;
}

}}}
