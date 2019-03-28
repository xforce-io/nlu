#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace ner {

class NameEntity : public basic::Fragment {
 private:
  typedef basic::Fragment Super;

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

  virtual int GetCategory() const = 0; 

  void Dump(JsonType &jsonType);

  virtual ~NameEntity() {}
};

NameEntity::NameEntity(size_t offset, size_t len) :
  Super(offset, len) {}

}}}
