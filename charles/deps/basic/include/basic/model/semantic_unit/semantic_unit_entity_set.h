#pragma once

#include "semantic_unit.h"
#include "../kg/entity.h"

namespace xforce { namespace nlu { namespace basic {

class SemanticUnitEntitySet : public SemanticUnit {
 public:
  struct Hash {
      size_t operator() (const std::shared_ptr<Entity>& entity) const {
        return std::hash<std::wstring>()(entity->Get());
      }
  };

  struct Comparator {
      bool operator() (
          const std::shared_ptr<Entity> &k0,
          const std::shared_ptr<Entity> &k1) const {
        return *k0 == *k1;
      }
  };

 public:
  SemanticUnitEntitySet();

 private:
  std::unordered_set<
          std::shared_ptr<Entity>,
          Hash,
          Comparator> container_;
};

}}}