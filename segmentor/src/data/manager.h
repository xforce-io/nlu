#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class BigramDict;
class NatureDict;
class NatureBigram;
class WordDict;  

class Manager {
 public:
  bool Init();

  const BigramDict& GetBigramDict() const { return *bigramDict_; }
  const NatureDict& GetNatureDict() const { return *natureDict_; }
  const NatureBigram& GetNatureBigram() const { return *natureBigram_; }
  const WordDict& GetWordDict() const { return *wordDict_; }

  inline static void SetBigramDict(BigramDict &bigramDict);
  inline static void SetNatureDict(NatureDict &natureDict);
  inline static void SetNatureBigram(NatureBigram &natureBigram);
  inline static void SetWordDict(WordDict &wordDict);

  virtual ~Manager();

  static Manager& Get() { return *manager_; }
  static void Tini();

 private:
  BigramDict *bigramDict_; 
  NatureDict *natureDict_;
  NatureBigram *natureBigram_;
  WordDict *wordDict_;

  static Manager *manager_;
};

void Manager::SetBigramDict(BigramDict &bigramDict) {
  manager_->bigramDict_ = &bigramDict;
}

void Manager::SetNatureDict(NatureDict &natureDict) {
  manager_->natureDict_ = &natureDict;
}

void Manager::SetNatureBigram(NatureBigram &natureBigram) {
  manager_->natureBigram_ = &natureBigram;
}

void Manager::SetWordDict(WordDict &wordDict) {
  manager_->wordDict_ = &wordDict;
}

}}}
