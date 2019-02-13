#pragma once

#include "../../../public.h"
#include "storage_key.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageItem;
class StorageKey;

class Storage {
 private:
  struct HashVal {
      size_t operator()(const StorageKey &storageKey) const{
        return storageKey.Hash();
      }
  };

 public:
  typedef std::unordered_map<
          StorageKey,
          StorageItem*,
          HashVal> Container;

 public:
  inline void Set(const StorageKey &key, const std::wstring &val);

  inline void Set(const StorageKey &key, StorageItem &storageItem);

  inline void SetStr(const StorageKey &key, const std::wstring &value);

  inline void Remove(const StorageKey &key);

  inline const StorageItem* Get(const StorageKey &key);

  inline const Container& Get() const;

  inline void GetStrs(std::unordered_map<std::wstring, std::wstring> &kvs);

  inline void Merge(const Storage &storage);

 private:
  Container container_;
};

}}}

#include "storage_item.h"

namespace xforce { namespace nlu { namespace milkie {

void Storage::Set(const StorageKey &key, const std::wstring &value) {
  auto iter = container_.find(key);
  if (iter != container_.end()) {
    iter->second->Set(value);
  }
}

void Storage::Set(const StorageKey &key, StorageItem &newItems) {
  StorageItem *storageItem = nullptr;
  auto iter = container_.find(key);
  if (iter == container_.end()) {
    storageItem = new StorageItem();
    container_.insert(std::make_pair(key, storageItem));
  } else {
    storageItem = iter->second;
  }
  storageItem->Add(newItems);
}

void Storage::SetStr(const StorageKey &key, const std::wstring &value) {
  auto iter = container_.find(key);
  if (iter == container_.end()) {
    container_.insert(std::make_pair(key, new StorageItem(&value)));
  } else {
    iter->second->Set(value);
  }
}

void Storage::Remove(const StorageKey &key) {
  container_.erase(key);
}

const StorageItem* Storage::Get(const StorageKey &key) {
  auto iter = container_.find(key);
  if (iter != container_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

const Storage::Container& Storage::Get() const {
  return container_;
}

void Storage::GetStrs(std::unordered_map<std::wstring, std::wstring> &kvs) {
  kvs.clear();
  for (auto iter = container_.begin(); iter != container_.end(); ++iter) {
    auto value = iter->second->GetAsString();
    if (nullptr != value) {
      std::wstring repr;
      iter->first.GetRepr(repr);
      kvs.insert(std::make_pair(repr, *value));
    }
  }
}

void Storage::Merge(const Storage &storage) {
  for (auto iter = storage.container_.begin(); iter != storage.container_.end(); ++iter) {
    auto iter2 = container_.find(iter->first);
    if (iter2 != container_.end()) {
      iter2->second->Add(*(iter->second));
    } else {
      container_.insert(std::make_pair(iter->first, iter->second));
    }
  }
}

}}}

