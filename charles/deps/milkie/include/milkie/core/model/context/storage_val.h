#pragma once

#include "../../../public.h"
#include "storage_item.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageVal {
 public: 
  inline explicit StorageVal(
          const std::wstring &item,
          size_t offset);

  inline StorageVal();

  inline void Set(const std::wstring &content, size_t offset);
  inline void Add(const StorageVal &storageItem);
  const std::vector<StorageItem>& Get() const { return items_; }
  inline const std::wstring* GetAsString() const;
  inline size_t Size() const;

  inline void Dump(JsonType &jsonType) const;

 private:   
   std::vector<StorageItem> items_;
};  

StorageVal::StorageVal(
        const std::wstring &content,
        size_t offset) {
  items_.push_back(StorageItem(content, offset));
}

StorageVal::StorageVal() {}

void StorageVal::Set(const std::wstring &value, size_t offset) {
  items_.push_back(StorageItem(value, offset));
}

void StorageVal::Add(const StorageVal &storageItem) {
  for (auto &item : storageItem.Get()) {
    items_.push_back(item);
  }
}

const std::wstring* StorageVal::GetAsString() const {
  if (items_.size() == 1) {
    return &(items_[0].GetContent());
  } else {
    return nullptr;
  }
}

size_t StorageVal::Size() const {
  return items_.size();
}

void StorageVal::Dump(JsonType &jsonType) const {
  for (size_t i=0; i < items_.size(); ++i) {
    items_[i].Dump(jsonType[i]);
  }
}

}}}
