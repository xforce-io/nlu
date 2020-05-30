#include "../semantic_unit_entity.h"
#include "../../kg/kg_adapter_mgr.h"

namespace xforce { namespace nlu { namespace basic {

typename Fragment::DistRes
SemanticUnitEntity::Distance(
        const Fragment &arg0,
        const Fragment &arg1) const {
  if (arg0.GetCategory() != Category::kSemantic ||
      arg1.GetCategory() != Category::kSemantic) {
    return Fragment::kUnknown;
  }

  if (((const SemanticUnit&)arg0).GetType() != Type::kSemanticUnitEntity ||
      ((const SemanticUnit&)arg1).GetType() != Type::kSemanticUnitEntity) {
    return Fragment::kUnknown;
  }

  auto &semanticUnitEntity0 = (const SemanticUnitEntity&)arg0;
  auto &semanticUnitEntity1 = (const SemanticUnitEntity&)arg1;
  size_t dist0 = KgAdapterMgr::Get()->DistCommonFather(
          *GetEntity(),
          *(semanticUnitEntity0.GetEntity()));
  size_t dist1 = KgAdapterMgr::Get()->DistCommonFather(
          *GetEntity(),
          *(semanticUnitEntity1.GetEntity()));
  if (dist0 != 0 && dist1 == 0) {
    return Fragment::kArg0;
  } else if (dist0 == 0 && dist1 != 0) {
    return Fragment::kArg1;
  } else if (dist0 != 0 && dist1 != 0) {
    return dist0 >= dist1 ? Fragment::kArg0 : Fragment::kArg1;
  }
  return Fragment::kUnknown;
}


}}}