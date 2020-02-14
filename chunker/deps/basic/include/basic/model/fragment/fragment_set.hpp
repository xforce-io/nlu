#pragma once

#include "../../public.h"
#include "fragment.h"
#include "../analysis_tracer/analysis_tracer.h"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
class FragmentSet {
 private:
  typedef FragmentSet<FragmentType> Self;
  typedef std::set<
      std::shared_ptr<FragmentType>, 
      typename FragmentType::Compare> Container;

 public:
  typedef typename Container::iterator Iter;

 public:
  explicit FragmentSet(const std::wstring &text);
  virtual ~FragmentSet();

  void Reset(const std::wstring &text);
  void Clear();

  virtual bool Add(std::shared_ptr<FragmentType> fragment);
  bool Add(const FragmentType &fragment);

  Self& operator=(const FragmentSet<FragmentType> &other);

  inline const Container& GetAll() const;
  inline std::shared_ptr<FragmentType> GetFragmentBefore(size_t offset) const;
  inline std::shared_ptr<FragmentType> GetFragmentBefore(
          size_t offset,
          std::function<bool(const FragmentType&)> filter) const;

  inline std::shared_ptr<FragmentType> GetFragmentAfter(size_t offset) const;
  inline std::shared_ptr<FragmentType> GetFragmentAfter(
          size_t offset,
          std::function<bool(const FragmentType&)> filter) const;
  inline std::shared_ptr<FragmentType> GetLongFragmentAfter(size_t offset) const;

  template <class OtherFragmentType>
  inline std::shared_ptr<FragmentType> Find(
          const std::shared_ptr<OtherFragmentType> &otherFragmentType) const;

  inline const typename FragmentSet<FragmentType>::Container::iterator Erase(
          const typename Container::iterator iter);

  inline const typename FragmentSet<FragmentType>::Container::iterator Erase(
          const typename Container::iterator from,
          const typename Container::iterator to);

  inline typename Container::iterator Begin();
  inline typename Container::iterator End();
  inline size_t Size() const;

  void Dump(JsonType &jsonType, const FragmentSet<FragmentType> *diff) const;

 protected:
  std::wstring *text_;

  Container fragments_;
};

template <typename FragmentType>
FragmentSet<FragmentType>::FragmentSet(const std::wstring &text) :
    text_(new std::wstring(text)) {}

template <typename FragmentType>
FragmentSet<FragmentType>::~FragmentSet() {
  XFC_DELETE(text_)
}

template <typename FragmentType>
void FragmentSet<FragmentType>::Reset(const std::wstring &text) {
  XFC_DELETE(text_)
  fragments_.clear();
  text_ = new std::wstring(text);  
}

template <typename FragmentType>
void FragmentSet<FragmentType>::Clear() {
  fragments_.clear();
}

template <typename FragmentType>
bool FragmentSet<FragmentType>::Add(std::shared_ptr<FragmentType> fragment) {
  if (fragment->GetOffset() < text_->length()) {
    bool ret;
    auto iter = fragments_.find(fragment);
    if (iter != fragments_.end()) {
      ret = (*iter)->Merge(*fragment);
    } else {
      ret = fragments_.insert(fragment).second;
    }
    return ret;
  }
  return false;
}

template <typename FragmentType>
bool FragmentSet<FragmentType>::Add(const FragmentType &fragment) {
  auto newFragment = std::make_shared<FragmentType>();
  *newFragment = fragment;
  return Add(newFragment);
}

template <typename FragmentType>
FragmentSet<FragmentType>& FragmentSet<FragmentType>::operator=(const FragmentSet<FragmentType> &other) {
  XFC_DELETE(text_)
  text_ = new std::wstring(*(other.text_));
  fragments_.clear();
  for (auto &fragment : other.fragments_) {
    fragments_.insert(std::make_shared<FragmentType>(*fragment));
  }
  return *this;
}

template <typename FragmentType>
const typename FragmentSet<FragmentType>::Container& FragmentSet<FragmentType>::GetAll() const {
  return fragments_;
}

template <typename FragmentType>
std::shared_ptr<FragmentType> FragmentSet<FragmentType>::GetFragmentBefore(size_t offset) const {
  for (auto &fragment : fragments_) {
    if (fragment->GetEnd() == offset) {
      return fragment;
    }
  }
  return nullptr;
}

template <typename FragmentType>
std::shared_ptr<FragmentType> FragmentSet<FragmentType>::GetFragmentBefore(
        size_t offset,
        std::function<bool(const FragmentType&)> filter) const {
  for (auto &fragment : fragments_) {
    if (fragment->GetEnd() == offset && filter(*fragment)) {
      return fragment;
    }
  }
  return nullptr;
}

template <typename FragmentType>
std::shared_ptr<FragmentType> FragmentSet<FragmentType>::GetFragmentAfter(size_t offset) const {
  for (auto &fragment : fragments_) {
    if (fragment->GetOffset() == offset) {
      return fragment;
    }
  }
  return nullptr;
}

template <typename FragmentType>
std::shared_ptr<FragmentType> FragmentSet<FragmentType>::GetFragmentAfter(
        size_t offset,
        std::function<bool(const FragmentType&)> filter) const {
  for (auto &fragment : fragments_) {
    if (fragment->GetOffset() == offset && filter(*fragment)) {
      return fragment;
    }
  }
  return nullptr;
}

template <typename FragmentType>
std::shared_ptr<FragmentType> FragmentSet<FragmentType>::GetLongFragmentAfter(size_t offset) const {
  std::shared_ptr<FragmentType> result;
  size_t maxLen = 0;
  for (auto &fragment : fragments_) {
    if (fragment->GetOffset() == offset && fragment->GetLen() > maxLen) {
      result = fragment;
      maxLen = fragment->GetLen();
    }
  }
  return result;
}

template <typename FragmentType>
template <typename OtherFragmentType>
std::shared_ptr<FragmentType> FragmentSet<FragmentType>::Find(
        const std::shared_ptr<OtherFragmentType> &otherFragmentType) const {
  if (!xforce::SameType<FragmentType, OtherFragmentType>::R) {
    return nullptr;
  }

  auto iter = fragments_.find(otherFragmentType);
  return iter != fragments_.end() ? *iter : nullptr;
}

template <typename FragmentType>
const typename FragmentSet<FragmentType>::Container::iterator FragmentSet<FragmentType>::Erase(
        const typename Container::iterator iter) {
  return fragments_.erase(iter);
}

template <typename FragmentType>
const typename FragmentSet<FragmentType>::Container::iterator FragmentSet<FragmentType>::Erase(
        const typename Container::iterator from,
        const typename Container::iterator to) {
  return fragments_.erase(from, to);
}

template <typename FragmentType>
typename FragmentSet<FragmentType>::Container::iterator
FragmentSet<FragmentType>::Begin() {
  return fragments_.begin();
}

template <typename FragmentType>
typename FragmentSet<FragmentType>::Container::iterator
FragmentSet<FragmentType>::End() {
  return fragments_.end();
}

template <typename FragmentType>
size_t FragmentSet<FragmentType>::Size() const {
  return fragments_.size();
}

template <typename FragmentType>
void FragmentSet<FragmentType>::Dump(
        JsonType &jsonType,
        const FragmentSet<FragmentType> *diff) const {
  size_t i=0;
  if (nullptr==diff) {
    for (auto &fragment : fragments_) {
      fragment->Dump(jsonType[fragment->GetCategory().c_str()][i]);
      ++i;
    }
  } else {
    for (auto &fragment : fragments_) {
      auto res = diff->Find(fragment);
      if (nullptr==res || !fragment->Same(*res)) {
        fragment->Dump(jsonType[fragment->GetCategory().c_str()][i]);
        ++i;
      }
    }
  }
}

}}}
