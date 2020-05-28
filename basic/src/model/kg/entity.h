#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace basic {

class Entity {
 public:
  inline explicit Entity(const std::wstring &name);

  const std::wstring& Get() const { return name_; }

  inline bool operator==(const Entity &other) const;

 private:
  std::wstring name_;
};

Entity::Entity(const std::wstring &name) :
    name_(name) {}

bool Entity::operator==(const Entity &other) const {
  return name_ == other.name_;
}

}}}