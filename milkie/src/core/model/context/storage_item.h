#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageItem {
 public: 
  inline explicit StorageItem(const std::shared_ptr<std::wstring> &item);
  inline StorageItem();

  inline void Set(const std::wstring &value);
  inline void Add(const StorageItem &storageItem);
  const Wstrings& Get() const { return items_; }
  inline std::wstring GetAsString() const;

 private:   
   std::vector<std::wstring> items_; 
};  

StorageItem::StorageItem(const std::shared_ptr<std::wstring> &item) {
  if (NULL != item->get()) {
    items_.push_back(*item);
  }
}

StorageItem::StorageItem() :
  this(NULL) {}

void StorageItem::Set(const std::wstring &value) {
  items_.push_back(value);
}

void StorageItem::Add(const StorageItem &storageItem) {
  for (auto &item : storageItem.Get()) {
    items_.push_back(item);
  }
}

const std::wstring* StorageItem::GetAsString() const {
  if (items_.length() == 1) {
    return &(items_[0]);
  } else {
    return NULL;
  }
}

}}}
