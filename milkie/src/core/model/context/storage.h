#pragma once

#include "../../../public.h"
#include "storage_key.h"
#include "storage_val.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageItem;

class Storage {
 public:
  typedef std::unordered_map<
          StorageKey,
          std::shared_ptr<StorageVal>,
          StorageKey::HashVal> Container;

 public:
  inline void Set(
      const StorageKey &key, 
      const std::wstring &content,
      size_t offset);

  inline void Set(const StorageKey &key, StorageVal &storageItem);

  inline void SetStr(
      const StorageKey &key, 
      const std::wstring &content,
      size_t offset);

  inline void Remove(const StorageKey &key);

  inline const std::shared_ptr<StorageVal> Get(const StorageKey &key);

  inline const Container& Get() const;

  inline void Get(typename Storage::Container &kvs);

  inline void Merge(const Storage &storage);

 private:
  Container container_;
};

}}}

#include "storage_val.h"

namespace xforce { namespace nlu { namespace milkie {

void Storage::Set(
    const StorageKey &key, 
    const std::wstring &content,
    size_t offset) {
  auto iter = container_.find(key);
  if (iter != container_.end()) {
    iter->second->Set(content, offset);
  }
}

void Storage::Set(const StorageKey &key, StorageVal &newItems) {
  std::shared_ptr<StorageVal> storageVal;
  auto iter = container_.find(key);
  if (iter == container_.end()) {
    storageVal = std::make_shared<StorageVal>();
    container_.insert(std::make_pair(key, storageVal));
  } else {
    storageVal = iter->second;
  }
  storageVal->Add(newItems);
}

void Storage::SetStr(
    const StorageKey &key, 
    const std::wstring &content,
    size_t offset) {
  auto iter = container_.find(key);
  if (iter == container_.end()) {
    container_.insert(std::make_pair(key, std::make_shared<StorageVal>(content, offset)));
  } else {
    iter->second->Set(content, offset);
  }
}

void Storage::Remove(const StorageKey &key) {
  container_.erase(key);
}

const std::shared_ptr<StorageVal> Storage::Get(const StorageKey &key) {
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

void Storage::Get(Storage::Container &kvs) {
  for (auto iter = container_.begin(); iter != container_.end(); ++iter) {
    auto value = iter->second;
    if (value != nullptr) {
      auto iter2 = kvs.find(iter->first);
      if (iter2 != kvs.end()) {
        iter2->second->Add(*value);
      } else {
        kvs.insert(std::make_pair(iter->first, value));
      }
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

