#pragma once

#include "../public.h"
#include "../model/pos/pos_tag.h"

namespace xforce { namespace nlu { namespace basic {

class GkbZk {
 public:
  GkbZk() {}

  bool Init(const std::string &filepath);

  inline const std::shared_ptr<std::vector<PosTag::Type>> GetPos(const std::wstring &str) const;

  virtual ~GkbZk() {}

 private: 
  void AddPosTag_(const std::wstring &key, PosTag::Type posTag);
  void BasicAddPosTag_(const std::wstring &key, PosTag::Type posTag); 

 private:
  std::unordered_map<std::wstring, std::shared_ptr<std::vector<PosTag::Type>>> charToPos_;
};

const std::shared_ptr<std::vector<PosTag::Type>> GkbZk::GetPos(const std::wstring &str) const {
  auto iter = charToPos_.find(str);
  if (iter != charToPos_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

}}}
