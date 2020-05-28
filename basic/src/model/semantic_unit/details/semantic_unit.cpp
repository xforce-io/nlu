#include "../semantic_unit.h"

namespace xforce { namespace nlu { namespace basic {

SemanticUnit::Type::Val SemanticUnit::GetSemanticUnitType(const std::wstring &type) {
  if (L"e" == type) {
    return SemanticUnit::Type::kSemanticUnitEntity;
  } else if (L"es" == type) {
    return SemanticUnit::Type::kSemanticUnitEntitySet;
  } else {
    return SemanticUnit::Type::kUndef;
  }
}

const std::wstring& SemanticUnit::Str(SemanticUnit::Type::Val type) {
  static const std::wstring kEntity = L"e";
  static const std::wstring kEntitySet = L"es";
  static const std::wstring kUndef = L"undef";
  switch (type) {
    case SemanticUnit::Type::kSemanticUnitEntity :
      return kEntity;
    case SemanticUnit::Type::kSemanticUnitEntitySet :
      return kEntitySet;
    default:
      return kUndef;
  }
}

}}}