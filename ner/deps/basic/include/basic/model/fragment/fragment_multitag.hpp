#pragma once

#include "../../public.h"
#include "fragment.h"
#include "fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

template <typename TagVal>
class FragmentMultitag : public Fragment {
 public:
  typedef Fragment Super;
  typedef FragmentMultitag<TagVal> Self;

 public:
  inline FragmentMultitag();
  inline FragmentMultitag(
          TagVal tagVal,
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

  inline FragmentMultitag(const FragmentMultitag<TagVal> &other);
  virtual ~FragmentMultitag() {}

  inline void SetTag(TagVal tagVal);
  inline void AddTag(TagVal tagVal);
  inline void RemoveTag(TagVal tagVal);
  inline bool Merge(const Self &other);
  inline Self& operator=(const Self &other);

  virtual const std::string& GetCategory() const = 0;
  size_t SizeTags() const { return tags_.size(); }
  const std::vector<TagVal>& GetTags() const { return tags_; }
  std::vector<TagVal>& GetTags() { return tags_; }
  inline TagVal GetTag() const;
  inline bool ContainTag(TagVal tagVal);

  inline std::wstring GetQuery(const std::wstring &sentence) const;

  virtual void Dump(JsonType &jsonType);

 protected:
  std::vector<TagVal> tags_;
};

template <typename TagVal>
FragmentMultitag<TagVal>::FragmentMultitag() :
    Fragment(0, 0) {}

template <typename TagVal>
FragmentMultitag<TagVal>::FragmentMultitag(
        TagVal tag,
        size_t offset,
        size_t len,
        uint32_t strategy) :
    Fragment(offset, len, strategy) {
  SetTag(tag);
}

template <typename TagVal>
FragmentMultitag<TagVal>::FragmentMultitag(
        size_t offset,
        size_t len,
        uint32_t strategy) :
    Fragment(offset, len, strategy) {}

template <typename TagVal>
FragmentMultitag<TagVal>::FragmentMultitag(
        size_t offset,
        uint32_t strategy) :
    Fragment(offset, 0, strategy) {}

template <typename TagVal>
FragmentMultitag<TagVal>::FragmentMultitag(const FragmentMultitag &other) :
    Super(other) {
  tags_ = other.tags_;
}

template <typename TagVal>
void FragmentMultitag<TagVal>::SetTag(TagVal tag) {
  tags_.clear();
  tags_.push_back(tag);
}

template <typename TagVal>
void FragmentMultitag<TagVal>::AddTag(TagVal tag) {
  for (auto &singleTag : tags_) {
    if (singleTag == tag) {
      return;
    }
  }
  tags_.push_back(tag);
}

template <typename TagVal>
void FragmentMultitag<TagVal>::RemoveTag(TagVal tag) {
  for (auto iter = tags_.begin(); iter != tags_.end(); ++iter) {
    if (*iter == tag) {
      tags_.erase(iter);
      return;
    }
  }
}

template <typename TagVal>
bool FragmentMultitag<TagVal>::Merge(const Self &other) {
  bool touched = false;
  for (auto &tag : other.GetTags()) {
    if (!ContainTag(tag)) {
      tags_.push_back(tag);
      touched = true;
    }
  }
  return touched;
}

template <typename TagVal>
FragmentMultitag<TagVal>& FragmentMultitag<TagVal>::operator=(const FragmentMultitag &other) {
  if (this == &other) {
    return *this;
  }

  Super::operator=(other);
  tags_ = other.tags_;
  return *this;
}

template <typename TagVal>
TagVal FragmentMultitag<TagVal>::GetTag() const {
  return tags_.size() == 1 ? tags_[0] : TagVal::kUndef;
}

template <typename TagVal>
bool FragmentMultitag<TagVal>::ContainTag(TagVal tag) {
  for (auto &singleTag : tags_) {
    if (singleTag == tag) {
      return true;
    }
  }
  return false;
}

template <typename TagVal>
std::wstring FragmentMultitag<TagVal>::GetQuery(const std::wstring &sentence) const {
  return sentence.substr(offset_, len_);
}

template <typename TagVal>
void FragmentMultitag<TagVal>::Dump(JsonType &jsonType) {
  Super::Dump(jsonType);
}

}}}
