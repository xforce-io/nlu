#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class Storage;
class StorageVal;

class Frame {
 public: 
  inline explicit Frame(ssize_t startPos);
  inline virtual ~Frame();

  inline void SetStartPos(ssize_t startPos);
  ssize_t GetStartPos() const { return startPos_; }
  const Storage &GetStorage() const { return *storage_; }
  Storage &GetStorage() { return *storage_; }
  inline void SetStoragePattern(const StorageVal &storageItem);
  inline std::shared_ptr<StorageVal> GetStoragePattern();

 private:
  ssize_t startPos_;
  Storage *storage_;
  std::shared_ptr<StorageVal> storagePattern_;
};  

}}}

#include "storage.h"
#include "storage_val.h"

namespace xforce { namespace nlu { namespace milkie {

Frame::Frame(ssize_t startPos) :
    storagePattern_(nullptr) {
  this->startPos_ = startPos;
  storage_ = new Storage();
}

Frame::~Frame() {
  XFC_DELETE(storage_)
}

void Frame::SetStartPos(ssize_t startPos) {
  this->startPos_ = startPos;
}

void Frame::SetStoragePattern(const StorageVal &storageItem) {
  if (storagePattern_ == nullptr) {
    storagePattern_ = std::make_shared<StorageVal>();
  }
  storagePattern_->Add(storageItem);
}

std::shared_ptr<StorageVal> Frame::GetStoragePattern() {
  return storagePattern_;
}

}}}
