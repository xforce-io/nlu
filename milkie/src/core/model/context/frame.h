#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageItem;  

class Frame {
 public: 
  inline explicit Frame(ssize_t startPos);
  virtual ~Frame();

  inline void SetStartPos(ssize_t startPos);
  ssize_t GetStartPos() const { return startPos_; }
  inline void SetStorage(const std::wstring &key, const std::wstring &value);
  inline void SetStorage(const std::wstring &key, StorageItem &newItems);
  inline void SetStorageStr(const std::wstring &key, const std::wstring &value);
  inline void RemoveStorage(const std::wstring &key);
  inline const StorageItem* GetStorage(const std::wstring &key);
  inline void SetStoragePattern(const StorageItem &storageItem);
  inline StorageItem* GetStoragePattern();
  inline void CopyStorage(const Frame &frame);
  void DumpStorge();

 private:
  ssize_t startPos_;
  std::unordered_map<std::wstring, StorageItem*> storage_;
  StorageItem *storagePattern_;
};  

}}}

#include "storage_item.h"

namespace xforce { namespace nlu { namespace milkie {

Frame::Frame(ssize_t startPos) :
    storagePattern_(nullptr) {
  this->startPos_ = startPos;    
}

void Frame::SetStartPos(ssize_t startPos) {
  this->startPos_ = startPos;
}

void Frame::SetStorage(const std::wstring &key, const std::wstring &value) {
  auto iter = storage_.find(key);
  if (iter != storage_.end()) {
    iter->second->Set(value);
  } else {
    storage_.insert(std::make_pair(key, new StorageItem(&value)));
  }
}

void Frame::SetStorage(const std::wstring &key, StorageItem &newItems) {
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

void Frame::SetStorageStr(const std::wstring &key, const std::wstring &value) {
  auto iter = storage_.find(key);
  if (iter == storage_.end()) {
    storage_.insert(std::make_pair(key, new StorageItem(&value)));
  } else {
    iter->second->Set(value);
  }
}

void Frame::RemoveStorage(const std::wstring &key) {
  storage_.erase(key);
}

const StorageItem* Frame::GetStorage(const std::wstring &key) {
  auto iter = storage_.find(key);
  if (iter != storage_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

void Frame::SetStoragePattern(const StorageItem &storageItem) {
  if (storagePattern_ == nullptr) {
    storagePattern_ = new StorageItem();
  }
  storagePattern_->Add(storageItem);
}

StorageItem* Frame::GetStoragePattern() {
  return storagePattern_;
}

void Frame::CopyStorage(const Frame &frame) {
  for (auto iter = frame.storage_.begin(); iter != frame.storage_.end(); ++iter) {
    auto iter2 = storage_.find(iter->first);
    if (iter2 != storage_.end()) {
      iter2->second->Add(*(iter->second));
    } else {
      storage_.insert(std::make_pair(iter->first, iter->second));
    }
  }
}

}}}
