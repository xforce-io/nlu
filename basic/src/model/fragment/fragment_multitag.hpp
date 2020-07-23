#pragma once

#include "../../public.h"
#include "fragment.h"
#include "fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

template <typename Tag>
class FragmentMultitag : public Fragment {
 public:
  typedef Fragment Super;
  typedef FragmentMultitag<Tag> Self;

 public:
  inline FragmentMultitag();
  inline FragmentMultitag(
          typename Tag::Val tagVal,
          size_t offset,
          size_t len,
          uint32_t strategy=0);

  inline FragmentMultitag(
          size_t offset,
          size_t len,
          uint32_t strategy=0);

  inline FragmentMultitag(
          size_t offset,
          uint32_t strategy=0);

  inline FragmentMultitag(const FragmentMultitag<Tag> &other);
  virtual ~FragmentMultitag() {}

  inline void SetTag(typename Tag::Val tagVal);
  virtual void AddTag(typename Tag::Val tagVal);
  inline void RemoveTag(typename Tag::Val tagVal);
  inline bool Merge(const Self &other);
  inline Self& operator=(const Self &other);

  size_t SizeTags() const { return tags_.size(); }
  const std::vector<typename Tag::Val>& GetTags() const { return tags_; }
  std::vector<typename Tag::Val>& GetTags() { return tags_; }
  inline typename Tag::Val GetTag() const;
  inline bool ContainTag(typename Tag::Val tagVal) const;
  virtual bool Same(const Fragment &other) const;
  virtual bool Contain(const Fragment &other) const;

  inline std::wstring GetQuery(const std::wstring &sentence) const;

  virtual void Dump(JsonType &jsonType) const;

 protected:
  std::vector<typename Tag::Val> tags_;
};

template <typename Tag>
FragmentMultitag<Tag>::FragmentMultitag() :
    Fragment(0, 0) {}

template <typename Tag>
FragmentMultitag<Tag>::FragmentMultitag(
        typename Tag::Val tag,
        size_t offset,
        size_t len,
        uint32_t strategy) :
    Fragment(offset, len, strategy) {
  SetTag(tag);
}

template <typename Tag>
FragmentMultitag<Tag>::FragmentMultitag(
        size_t offset,
        size_t len,
        uint32_t strategy) :
    Fragment(offset, len, strategy) {}

template <typename Tag>
FragmentMultitag<Tag>::FragmentMultitag(
        size_t offset,
        uint32_t strategy) :
    Fragment(offset, 0, strategy) {}

template <typename Tag>
FragmentMultitag<Tag>::FragmentMultitag(const FragmentMultitag &other) :
    Super(other) {
  tags_ = other.tags_;
}

template <typename Tag>
void FragmentMultitag<Tag>::SetTag(typename Tag::Val tag) {
  tags_.clear();
  tags_.push_back(tag);
}

template <typename Tag>
void FragmentMultitag<Tag>::AddTag(typename Tag::Val tag) {
  for (auto &singleTag : tags_) {
    if (singleTag == tag) {
      return;
    }
  }
  tags_.push_back(tag);
}

template <typename Tag>
void FragmentMultitag<Tag>::RemoveTag(typename Tag::Val tag) {
  for (auto iter = tags_.begin(); iter != tags_.end(); ++iter) {
    if (*iter == tag) {
      tags_.erase(iter);
      return;
    }
  }
}

template <typename Tag>
bool FragmentMultitag<Tag>::Merge(const Self &other) {
  bool touched = false;
  for (auto &tag : other.GetTags()) {
    if (!ContainTag(tag)) {
      tags_.push_back(tag);
      strategy_ = other.strategy_;
      touched = true;
    }
  }
  return touched;
}

template <typename Tag>
FragmentMultitag<Tag>& FragmentMultitag<Tag>::operator=(const FragmentMultitag<Tag> &other) {
  if (this == &other) {
    return *this;
  }

  Super::operator=(other);
  tags_ = other.tags_;
  return *this;
}

template <typename Tag>
typename Tag::Val FragmentMultitag<Tag>::GetTag() const {
  return tags_.size() == 1 ? tags_[0] : Tag::kUndef;
}

template <typename Tag>
bool FragmentMultitag<Tag>::ContainTag(typename Tag::Val tag) const {
  for (auto &singleTag : tags_) {
    if (singleTag == tag) {
      return true;
    }
  }
  return false;
}

template <typename Tag>
bool FragmentMultitag<Tag>::Same(const Fragment &fragment) const {
  auto &other = SCAST<const FragmentMultitag<Tag>&>(fragment);
  if (!Fragment::Same(other) || tags_.size() != other.tags_.size()) {
    return false;
  }

  for (auto &tag : tags_) {
    bool ret = false;
    for (auto &otherTag : other.tags_) {
      if (tag == otherTag) {
        ret = true;
        break;
      }
    }

    if (!ret) {
      return false;
    }
  }
  return true;
}

template <typename Tag>
bool FragmentMultitag<Tag>::Contain(const Fragment &fragment) const {
  if (offset_ != fragment.GetOffset() || len_ != fragment.GetLen()) {
    return false;
  }

  auto &other = SCAST<const FragmentMultitag<Tag>&>(fragment);
  for (auto &tag : other.tags_) {
    if (!tags_.find(tag)) {
      return false;
    }
  }
  return true;
}

template <typename Tag>
std::wstring FragmentMultitag<Tag>::GetQuery(const std::wstring &sentence) const {
  return sentence.substr(offset_, len_);
}

template <typename Tag>
void FragmentMultitag<Tag>::Dump(JsonType &jsonType) const {
  Super::Dump(jsonType);
}

}}}
