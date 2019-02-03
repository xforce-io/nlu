#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class Storage;
class StorageItem;

class Frame {
 public: 
  inline explicit Frame(ssize_t startPos);
  inline virtual ~Frame();

  inline void SetStartPos(ssize_t startPos);
  ssize_t GetStartPos() const { return startPos_; }
  const Storage &GetStorage() const { return *storage_; }
  Storage &GetStorage() { return *storage_; }
  inline void SetStoragePattern(const StorageItem &storageItem);
  inline StorageItem* GetStoragePattern();

 private:
  ssize_t startPos_;
  Storage *storage_;
  StorageItem *storagePattern_;
};  

}}}

#include "storage.h"
#include "storage_item.h"

namespace xforce { namespace nlu { namespace milkie {

Frame::Frame(ssize_t startPos) :
    storagePattern_(nullptr) {
  this->startPos_ = startPos;    
}

Frame::~Frame() {
  XFC_DELETE(storagePattern_)
  XFC_DELETE(storage_)
}

void Frame::SetStartPos(ssize_t startPos) {
  this->startPos_ = startPos;
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

}}}
