#pragma once

#include "semantic_unit.h"

namespace xforce { namespace nlu { namespace basic {

class Entity;

class SemanticUnitEntity : public SemanticUnit {
 public:
  Type::Val GetType() const { return Type::kSemanticUnitEntity; }

  const std::shared_ptr<Entity> GetEntity() const { return entity_; }
  std::shared_ptr<Entity> GetEntity() { return entity_; }

  ssize_t Distance(const Fragment &other) const;

 private:
  std::shared_ptr<Entity> entity_;
};

}}}
