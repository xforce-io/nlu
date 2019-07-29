#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class StorageItem {
 public:
  inline StorageItem(const std::wstring &content, size_t offset);

  inline void SetContent(const std::wstring &content);
  inline void SetOffset(size_t offset);

  const std::wstring& GetContent() const { return content_; }
  size_t GetOffset() const { return offset_; }
  inline size_t GetLen() const;

 private:
  std::wstring content_;
  size_t offset_;
};

StorageItem::StorageItem(const std::wstring &content, size_t offset) :
    content_(content),
    offset_(offset) {}

void StorageItem::SetContent(const std::wstring &content) {
  content_ = content;
}

void StorageItem::SetOffset(size_t offset) {
  offset_ = offset;
}

size_t StorageItem::GetLen() const {
  return content_.length();
}

}}}
