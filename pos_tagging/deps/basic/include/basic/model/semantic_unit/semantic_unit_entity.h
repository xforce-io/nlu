#pragma once

#include "semantic_unit.h"

namespace xforce { namespace nlu { namespace basic {

class Entity;

class SemanticUnitEntity : public SemanticUnit {
 public:
  SemanticUnitEntity();

  inline Category GetCategory() const { return kSemanticUnitEntity; }

  const std::shared_ptr<Entity> GetEntity() const { return entity_; }
  std::shared_ptr<Entity> GetEntity() { return entity_; }

 private:
  std::shared_ptr<Entity> entity_;
};

}}}