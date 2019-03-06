#pragma once

#include "../public.h"
#include "../model/pos/pos.h"

namespace xforce { namespace nlu { namespace basic {

class GkbZk {
 public:
  GkbZk() {}

  bool Init(const std::string &filepath);

  inline std::shared_ptr<std::vector<Pos::Type>> GetPos(const std::wstring &str);

  virtual ~GkbZk();

 private:
  std::unordered_map<std::wstring, std::shared_ptr<std::vector<Pos::Type>>> charToPos_;
};

std::shared_ptr<std::vector<basic::Pos::Type>> GkbZk::GetPos(const std::wstring &str) {
  auto iter = charToPos_.find(str);
  if (iter != charToPos_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

}}}