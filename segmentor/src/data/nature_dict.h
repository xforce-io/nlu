#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor { 

class Nature;  

class NatureDict {
 private:   
  typedef std::unordered_map<std::string, Nature*> Container; 
  
 public:
  NatureDict() {} 

  bool Init(const std::string &dictpath);
  inline const Nature* GetNature(const std::string &name) const;
  uint32_t GetIndexSize() const { return indexSize_; }

  virtual ~NatureDict();

 private:
  Container container_;
  uint32_t indexSize_;
};

const Nature* NatureDict::GetNature(const std::string &name) const {
  auto iter = container_.find(name);
  if (iter != container_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

}}}
