#pragma once

#include "../public.h"
#include "fragment/fragment.h"
#include "fragment/fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

class NameEntity : public basic::Fragment {
 public:
  typedef Fragment Super;
  typedef FragmentSet<NameEntity> Set;

 public:
  enum Category {
    kCategoryNone = -1,
    kCategoryTime = 1,
    kCategoryNumber = 2,
    kCategoryPublication = 3,
    kCategoryName = 4,
    kCategoryOther = 100,
  };

 public: 
  inline NameEntity(size_t offset, size_t len);
  virtual ~NameEntity();

  virtual int GetNECategory() const = 0;
  const std::string& GetCategory() const;

  void Dump(JsonType &jsonType);
};

NameEntity::NameEntity(size_t offset, size_t len) :
  Super(offset, len) {}

}}}
