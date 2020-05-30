#pragma once

#include "semantic_unit.h"

namespace xforce { namespace nlu { namespace basic {

class Entity;

class SemanticUnitEntity : public SemanticUnit {
 public:
  SemanticUnitEntity();

  const std::shared_ptr<Entity> GetEntity() const { return entity_; }
  std::shared_ptr<Entity> GetEntity() { return entity_; }

  DistRes Distance(const Fragment &arg0, const Fragment &arg1) const;

 private:
  std::shared_ptr<Entity> entity_;
};

}}}