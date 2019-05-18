#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class BigramDict {
 private:
  typedef std::unordered_map<std::wstring, uint32_t> Inner; 
  typedef std::unordered_map<std::wstring, Inner*> Container;

 private:
  static const std::wstring kMarkNum;
 
 public:
  BigramDict() {}

  bool Init(const std::string &dictpath);
  uint32_t GetFreq(const std::wstring &word0, const std::wstring &word1) const;

  virtual ~BigramDict();

 private: 
  void AddToDict_(const std::wstring &word0, const std::wstring &word1, uint32_t freq);
  const std::wstring& WordMapper_(const std::wstring &word) const;

 private:
  Container container_;
};

}}}
