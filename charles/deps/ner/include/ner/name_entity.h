#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace ner {

class NameEntity {
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

  size_t GetOffset() const { return offset_; }
  size_t GetLen() const { return len_; }

  void Dump(JsonType &jsonType);

  virtual ~NameEntity() {}
 
 protected:
  size_t offset_; 
  size_t len_;
};

NameEntity::NameEntity(size_t offset, size_t len) :
  offset_(offset),
  len_(len) {}

}}}
