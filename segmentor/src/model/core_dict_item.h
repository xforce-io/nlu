#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class CoreDictNatures;

class CoreDictItem {
 public:
  bool Init(const std::vector<std::string> &items);

  const std::wstring& GetName() const { return name_; }
  inline size_t GetFreq() const;

  virtual ~CoreDictItem();

 private: 
  std::wstring name_;
  CoreDictNatures *coreDictNatures_;
};  

}}}

#include "core_dict_natures.h"

namespace xforce { namespace nlu { namespace segmentor {

size_t CoreDictItem::GetFreq() const { 
  return coreDictNatures_->GetFreq(); 
}

}}}
