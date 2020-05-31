#include "../semantic_unit_entity.h"
#include "../../kg/kg_adapter_mgr.h"

namespace xforce { namespace nlu { namespace basic {

ssize_t SemanticUnitEntity::Distance(const Fragment &other) const {
  if (other.GetCategory() != Category::kSemantic) {
    return -1;
  }

  if (((const SemanticUnit&)other).GetType() != Type::kSemanticUnitEntity) {
    return -1;
  }

  auto &otherEntity = (const SemanticUnitEntity&)other;
  return KgAdapterMgr::Get()->DistCommonFather(
          *GetEntity(),
          *(otherEntity.GetEntity()));
}

}}}