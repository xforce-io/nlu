#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageItem {
 public: 
  inline explicit StorageItem(const std::wstring *item);
  inline StorageItem();

  inline void Set(const std::wstring &value);
  inline void Add(const StorageItem &storageItem);
  const Wstrings& Get() const { return items_; }
  inline const std::wstring* GetAsString() const;

 private:   
   std::vector<std::wstring> items_; 
};  

StorageItem::StorageItem(const std::wstring *item) {
  if (nullptr != item) {
    items_.push_back(*item);
  }
}

StorageItem::StorageItem() :
  StorageItem(nullptr) {}

void StorageItem::Set(const std::wstring &value) {
  items_.push_back(value);
}

void StorageItem::Add(const StorageItem &storageItem) {
  for (auto &item : storageItem.Get()) {
    items_.push_back(item);
  }
}

const std::wstring* StorageItem::GetAsString() const {
  if (items_.size() == 1) {
    return &(items_[0]);
  } else {
    return nullptr;
  }
}

}}}
