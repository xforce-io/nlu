#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageKey {
 public:
  struct HashVal {
      size_t operator()(const StorageKey &storageKey) const{
        return storageKey.Hash();
      }
  };

 public:
  StorageKey() {}

  inline StorageKey(
          const std::wstring *space,
          const std::wstring *item);

  inline StorageKey(
          const wchar_t *space,
          const wchar_t *item);

  inline void SetSpace(const std::wstring *space);
  inline void SetItem(const std::wstring *item);

  inline const std::wstring *GetSpace() const;
  inline const std::wstring *GetItem() const;

  inline bool operator==(const StorageKey &storageKey) const;
  inline void operator=(const StorageKey &storageKey);
  inline size_t Hash() const;

  inline void GetRepr(std::wstring &repr) const;
  inline void Dump(JsonType &jsonType) const;

 private:
  std::shared_ptr<std::wstring> space_;
  std::shared_ptr<std::wstring> item_;
};

StorageKey::StorageKey(
        const std::wstring *space,
        const std::wstring *item) {
  if (nullptr != space) {
    space_ = std::make_shared<std::wstring>(*space);
  }

  if (nullptr != item) {
    item_ = std::make_shared<std::wstring>(*item);
  }
}

StorageKey::StorageKey(
        const wchar_t *space,
        const wchar_t *item) {
  if (nullptr != space) {
    space_ = std::make_shared<std::wstring>(space);
  }

  if (nullptr != item) {
    item_ = std::make_shared<std::wstring>(item);
  }
}

void StorageKey::SetSpace(const std::wstring *space) {
  if (nullptr != space) {
    space_ = std::make_shared<std::wstring>(*space);
  } else {
    space_ = nullptr;
  }
}

void StorageKey::SetItem(const std::wstring *item) {
  if (nullptr != item) {
    item_ = std::make_shared<std::wstring>(*item);
  } else {
    item_ = nullptr;
  }
}

const std::wstring* StorageKey::GetSpace() const {
  return space_ != nullptr ? space_.get() : nullptr;
}

const std::wstring* StorageKey::GetItem() const {
  return item_ != nullptr ? item_.get() : nullptr;
}

bool StorageKey::operator==(const StorageKey &storageKey) const {
  bool ret = ((GetSpace() == nullptr &&
              storageKey.GetSpace() == nullptr) ||
          (GetSpace() != nullptr &&
              storageKey.GetSpace() != nullptr &&
              *GetSpace() == *storageKey.GetSpace())) &&
      ((GetItem() == nullptr &&
              storageKey.GetItem() == nullptr) ||
          (GetItem() != nullptr &&
               storageKey.GetItem() != nullptr &&
               *GetItem() == *storageKey.GetItem()));
  return ret;
}

void StorageKey::operator=(const StorageKey &storageKey) {
  space_ = storageKey.space_;
  item_ = storageKey.item_;
}

size_t StorageKey::Hash() const {
  size_t v0=0, v1=0;
  if (GetSpace() != nullptr) {
    v0 = std::hash<std::wstring>()(*GetSpace());
  }

  if (GetItem() != nullptr) {
    v1 = std::hash<std::wstring>()(*GetItem());
  }
  return v0 + 31 * v1;
}

void StorageKey::GetRepr(std::wstring &repr) const {
  std::wstringstream ss;
  if (nullptr != space_) {
    ss << *space_;
  }
  ss << L'/';
  if (nullptr != item_) {
    ss << *item_;
  }
  repr = ss.str();
}

void StorageKey::Dump(JsonType &jsonType) const {
  std::wstring repr;
  GetRepr(repr);
  jsonType["repr"] = repr;
}

}}}
