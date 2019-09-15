#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class ForbidItem {
 public:
  ForbidItem() {}
  inline ForbidItem(
          size_t categoryRule,
          size_t offset,
          size_t len);

  inline void SetCategoryRule(size_t categoryRule);
  inline void SetOffset(size_t offset);
  inline void SetLen(size_t len);

  size_t GetCategoryRule() const { return categoryRule_; }
  size_t GetOffset() const { return offset_; }
  size_t GetLen() const { return len_; }

 private:
  size_t categoryRule_;
  size_t offset_;
  size_t len_;
};

ForbidItem::ForbidItem(
        size_t categoryRule,
        size_t offset,
        size_t len) :
    categoryRule_(categoryRule),
    offset_(offset),
    len_(len) {}

void ForbidItem::SetCategoryRule(size_t categoryRule) {
  categoryRule_ = categoryRule;
}

void ForbidItem::SetOffset(size_t offset) {
  offset_ = offset;
}

void ForbidItem::SetLen(size_t len) {
  len_ = len;
}

}}}
