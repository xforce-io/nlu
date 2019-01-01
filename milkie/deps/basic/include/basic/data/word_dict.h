#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace basic {

class DictItem;

class WordDict {
 private:
  typedef std::unordered_map<std::wstring, std::vector<DictItem*>> Container; 
 
 private: 
  static size_t kMaxSizeDict;
 
 public: 
  bool Init(const std::string &filepath);

  inline const std::vector<DictItem*>* GetDictItems(const std::wstring &word) const;

  virtual ~WordDict();

 private: 
  bool AddItem_(const std::string &name, const JsonType &jsonType);

 public:
  Container container_;
};

const std::vector<DictItem*>* WordDict::GetDictItems(const std::wstring &word) const {
  auto iter = container_.find(word);
  if (container_.end() != iter) {
    return &(iter->second);
  } else {
    return NULL;
  }
}

}}}
