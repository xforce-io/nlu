#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class BigramDict;
class NatureDict;
class NatureBigram;
class Surname;
class WordDict;  

class Manager {
 public:
  bool Init();

  const BigramDict& GetBigramDict() const { return *bigramDict_; }
  const NatureDict& GetNatureDict() const { return *natureDict_; }
  const NatureBigram& GetNatureBigram() const { return *natureBigram_; }
  const Surname& GetSurname() const { return *surname_; }
  const WordDict& GetWordDict() const { return *wordDict_; }

  inline static void SetBigramDict(BigramDict &bigramDict);
  inline static void SetNatureDict(NatureDict &natureDict);
  inline static void SetNatureBigram(NatureBigram &natureBigram);
  inline static void SetSurname(Surname &surname);
  inline static void SetWordDict(WordDict &wordDict);

  static Manager& Get() { return *manager_; }

 private:
  BigramDict *bigramDict_; 
  NatureDict *natureDict_;
  NatureBigram *natureBigram_;
  Surname *surname_;
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

void Manager::SetSurname(Surname &surname) {
  manager_->surname_ = &surname;
}

void Manager::SetWordDict(WordDict &wordDict) {
  manager_->wordDict_ = &wordDict;
}

}}
