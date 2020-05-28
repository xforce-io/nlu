#pragma once

#include "../../public.h"
#include "fragment.h"
#include "fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

class NameEntity : public Fragment {
 public:
  typedef Fragment Super;
  typedef FragmentSet<NameEntity> Set;

 public:
  enum NECategory {
    kCategoryNone = -1,
    kCategoryTime = 1,
    kCategoryNumber = 2,
    kCategoryPublication = 3,
    kCategoryName = 4,
    kCategoryOther = 100,
  };

 public: 
  inline NameEntity();
  inline NameEntity(size_t offset, size_t len);
  inline NameEntity(const NameEntity &other);
  virtual ~NameEntity();

  int GetNECategory() const { return kCategoryOther; }
  Fragment::Category GetCategory() const { return kNameEntity; }

  void Dump(JsonType &jsonType) const;
};

NameEntity::NameEntity() :
    Fragment(-1, -1) {}

NameEntity::NameEntity(size_t offset, size_t len) :
  Super(offset, len) {}

NameEntity::NameEntity(const NameEntity &other) :
    Super(other) {}

}}}
