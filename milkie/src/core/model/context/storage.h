#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageItem;

class Storage {
 public:
  inline void Set(const std::wstring &key, const std::wstring &val);

  inline void Set(const std::wstring &key, StorageItem &storageItem);

  inline void SetStr(const std::wstring &key, const std::wstring &value);

  inline void Remove(const std::wstring &key);

  inline const StorageItem *Get(const std::wstring &key);

  inline const std::unordered_map<std::wstring, StorageItem*> Get() const;

  inline void GetStrs(std::unordered_map<std::wstring, std::wstring> &kvs);

  inline void Merge(const Storage &storage);

 private:
  std::unordered_map<std::wstring, StorageItem*> storage_;
};

}}}

#include "storage_item.h"

namespace xforce { namespace nlu { namespace milkie {

void Storage::Set(const std::wstring &key, const std::wstring &value) {
  auto iter = storage_.find(key);
  if (iter != storage_.end()) {
    iter->second->Set(value);
  }
}

void Storage::Set(const std::wstring &key, StorageItem &newItems) {
  StorageItem *storageItem = nullptr;
  auto iter = storage_.find(key);
  if (iter == storage_.end()) {
    storageItem = new StorageItem();
    storage_.insert(std::make_pair(key, storageItem));
  } else {
    storageItem = iter->second;
  }
  newItems.Add(*storageItem);
}

void Storage::SetStr(const std::wstring &key, const std::wstring &value) {
  auto iter = storage_.find(key);
  if (iter == storage_.end()) {
    storage_.insert(std::make_pair(key, new StorageItem(&value)));
  } else {
    iter->second->Set(value);
  }
}

void Storage::Remove(const std::wstring &key) {
  storage_.erase(key);
}

const StorageItem* Storage::Get(const std::wstring &key) {
  auto iter = storage_.find(key);
  if (iter != storage_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

const std::unordered_map<std::wstring, StorageItem*> Storage::Get() const {
  return storage_;
}

void Storage::GetStrs(std::unordered_map<std::wstring, std::wstring> &kvs) {
  kvs.clear();
  for (auto iter = storage_.begin(); iter != storage_.end(); ++iter) {
    auto value = iter->second->GetAsString();
    if (nullptr != value) {
      kvs.insert(std::make_pair(iter->first, *value));
    }
  }
}

void Storage::Merge(const Storage &storage) {
  for (auto iter = storage.storage_.begin(); iter != storage.storage_.end(); ++iter) {
    auto iter2 = storage_.find(iter->first);
    if (iter2 != storage_.end()) {
      iter2->second->Add(*(iter->second));
    } else {
      storage_.insert(std::make_pair(iter->first, iter->second));
    }
  }
}

}}}

