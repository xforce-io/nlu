#pragma once

#include "../../public.h"
#include "fragment.h"

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

  virtual bool Add(std::shared_ptr<FragmentType> fragment);
  bool Add(const FragmentType &fragment);

  Self& operator=(const FragmentSet<FragmentType> &other);

  inline const Container& GetAll() const;
  inline std::shared_ptr<FragmentType> GetFragmentBefore(size_t offset);
  inline std::shared_ptr<FragmentType> GetFragmentAfter(size_t offset);

  inline const typename FragmentSet<FragmentType>::Container::iterator Erase(
          const typename Container::iterator iter);

  inline const typename FragmentSet<FragmentType>::Container::iterator Erase(
          const typename Container::iterator from,
          const typename Container::iterator to);

  inline typename Container::iterator Begin();
  inline typename Container::iterator End();
  inline size_t Size() const;

  void Dump(JsonType &jsonType);

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
bool FragmentSet<FragmentType>::Add(std::shared_ptr<FragmentType> fragment) {
  if (fragment->GetOffset() < text_->length()) {
    auto iter = fragments_.find(fragment);
    if (iter != fragments_.end()) {
      return (*iter)->Merge(*fragment);
    } else {
      return fragments_.insert(fragment).second;
    }
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
    fragments_.insert(fragment);
  }
  return *this;
}

template <typename FragmentType>
const typename FragmentSet<FragmentType>::Container& FragmentSet<FragmentType>::GetAll() const {
  return fragments_;
}

template <typename FragmentType>
std::shared_ptr<FragmentType> FragmentSet<FragmentType>::GetFragmentBefore(size_t offset) {
  for (auto &fragment : fragments_) {
    if (fragment->GetOffset() + fragment->GetLen() == offset) {
      return fragment;
    }
  }
  return nullptr;
}

template <typename FragmentType>
std::shared_ptr<FragmentType> FragmentSet<FragmentType>::GetFragmentAfter(size_t offset) {
  for (auto &fragment : fragments_) {
    if (fragment->GetOffset() == offset) {
      return fragment;
    }
  }
  return nullptr;
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
void FragmentSet<FragmentType>::Dump(JsonType &jsonType) {
  jsonType["text"] = *StrHelper::Wstr2Str(*text_);
  size_t i=0;
  for (auto &fragment : fragments_) {
    fragment->Dump(jsonType[fragment->GetCategory().c_str()][i]);
    ++i;
  }
}

}}}
