#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class CoreDictItem;
class SimpleTrie;

class WordDict {
 private:
  typedef std::tr1::unordered_map<std::string, CoreDictItem*> Container; 
 
 public: 
  bool Init(const std::vector<std::string> &filepaths);

  void PrefixMatch(
      IN const std::string &query, 
      OUT std::vector<const CoreDictItem*> &coreDictItems) const;
  const CoreDictItem* GetCoreDictItem(const std::string &word) const;
  ssize_t GetFreq(const std::string &word) const; 

  virtual ~WordDict();

  static size_t GetCntWord() { return 2079997; }
 
 private: 
  bool Init_(const std::string &filepath);

 public:
  Container container_;
  xforce::SimpleTrie *simpleTrie_;
};

}}
