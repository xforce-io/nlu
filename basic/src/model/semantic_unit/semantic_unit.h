#pragma once

#include "../fragment/fragment.h"
#include "../fragment/fragment_set.hpp"

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
  typedef FragmentSet<SemanticUnit> Set;

 public:
  SemanticUnit();

  Fragment::Category GetCategory() const { return kSemantic; }

  virtual Type::Val GetType() const = 0;

 public:
  static SemanticUnit::Type::Val GetSemanticUnitType(const std::wstring &type);
  static const std::wstring& Str(SemanticUnit::Type::Val type);
};

}}}
