#pragma once

#include "public.h"

class BigramDict {
 private:
  typedef std::unordered_map<std::string, uint32_t> Inner; 
  typedef std::unordered_map<std::string, Inner*> Container;
 
 public:
  BigramDict() {}

  bool Init(const std::string &dictpath);
  uint32_t getFreq(const std::string &word0, const std::string &word1); 

  virtual ~BigramDict();

 private: 
  void addToDict(const std::string &word0, const std::string &word1, uint32_t freq);

 private:
  Container container_;
};
