#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class BigramDict {
 private:
  typedef std::tr1::unordered_map<std::wstring, uint32_t> Inner; 
  typedef std::tr1::unordered_map<std::wstring, Inner*> Container;
 
 public:
  BigramDict() {}

  bool Init(const std::string &dictpath);
  uint32_t GetFreq(const std::wstring &word0, const std::wstring &word1) const;

  virtual ~BigramDict();

 private: 
  void AddToDict(const std::wstring &word0, const std::wstring &word1, uint32_t freq);

 private:
  Container container_;
};

}}}
