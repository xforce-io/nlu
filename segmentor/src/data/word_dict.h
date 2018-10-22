#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class CoreDictItem;

class WordDict {
 private:
  typedef std::tr1::unordered_map<std::string, CoreDictItem*> Container; 
 
 public: 
  bool Init(const std::vector<std::string> &filepaths);

  void PrefixMatch(
      IN const std::string &query, 
      OUT std::vector<const CoreDictItem*> &coreDictItems);
  const CoreDictItem* GetCoreDictItem(const std::string &word) const;
  ssize_t GetFreq(const std::string &word); 

  virtual ~WordDict();
 
 private: 
  bool Init_(const std::string &filepath);

 public:
  Container container_;
  SimpleTrie *simpleTrie_;
};

}}
