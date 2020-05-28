#pragma once

#include "../fragment/fragment.h"

namespace xforce { namespace nlu { namespace basic {

class SemanticUnit : public Fragment {
 public:
    struct Type {
      enum Val {
        kSemanticUnitEntity,
        kSemanticUnitEntitySet,
        kUndef,
      };
    };

 public:
  SemanticUnit();

  Fragment::Category GetCategory() const { return kSemantic; }

  virtual Type::Val GetType() const;

 public:
  static SemanticUnit::Type::Val GetSemanticUnitType(const std::wstring &type);
  static const std::wstring& Str(SemanticUnit::Type::Val type);
};

}}}