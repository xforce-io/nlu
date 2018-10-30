#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class BigramDict {
 private:
  typedef std::tr1::unordered_map<std::string, uint32_t> Inner; 
  typedef std::tr1::unordered_map<std::string, Inner*> Container;
 
 public:
  BigramDict() {}

  bool Init(const std::string &dictpath);
  uint32_t GetFreq(const std::string &word0, const std::string &word1) const;

  virtual ~BigramDict();

 private: 
  void AddToDict(const std::string &word0, const std::string &word1, uint32_t freq);

 private:
  Container container_;
};

}}
