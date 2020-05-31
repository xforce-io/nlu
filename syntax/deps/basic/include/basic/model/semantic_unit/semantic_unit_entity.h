#pragma once

#include "semantic_unit.h"

namespace xforce { namespace nlu { namespace basic {

class Entity;

class SemanticUnitEntity : public SemanticUnit {
 public:
  const std::shared_ptr<Entity> GetEntity() const { return entity_; }
  std::shared_ptr<Entity> GetEntity() { return entity_; }

  inline ssize_t Distance(const Fragment &other) const;

 private:
  std::shared_ptr<Entity> entity_;
};

}}}