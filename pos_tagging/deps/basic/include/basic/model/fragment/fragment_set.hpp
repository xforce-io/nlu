#pragma once

#include "../../public.h"
#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
class FragmentSet {
 private:
  typedef FragmentSet<FragmentType> Self;

 public:
  explicit FragmentSet(const std::wstring &text);
  virtual ~FragmentSet();

  void Reset(const std::wstring &text);

  virtual void Add(std::shared_ptr<FragmentType> fragment);
  void Add(const FragmentType &fragment);

  Self& operator=(const FragmentSet<FragmentType> &other);

  inline const std::vector<std::shared_ptr<FragmentType>> GetAll() const;

  inline const std::shared_ptr<FragmentType>& operator[](size_t i) const;
  inline std::shared_ptr<FragmentType>& operator[](size_t i);

  inline size_t Size() const;

  void Dump(JsonType &jsonType);

 protected:
  std::wstring *text_;

  std::vector<std::shared_ptr<FragmentType>> fragments_;
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
void FragmentSet<FragmentType>::Add(std::shared_ptr<FragmentType> fragment) {
  fragments_.push_back(fragment);
}

template <typename FragmentType>
void FragmentSet<FragmentType>::Add(const FragmentType &fragment) {
  auto newFragment = std::make_shared<FragmentType>();
  *newFragment = fragment;
  Add(newFragment);
}

template <typename FragmentType>
FragmentSet<FragmentType>& FragmentSet<FragmentType>::operator=(const FragmentSet<FragmentType> &other) {
  XFC_DELETE(text_)
  text_ = new std::wstring(*(other.text_));
  fragments_.clear();
  for (auto &fragment : other.fragments_) {
    fragments_.push_back(fragment);
  }
  return *this;
}

template <typename FragmentType>
const std::vector<std::shared_ptr<FragmentType>> FragmentSet<FragmentType>::GetAll() const {
  return fragments_;
}

template <typename FragmentType>
const std::shared_ptr<FragmentType>& FragmentSet<FragmentType>::operator[](size_t i) const {
  return fragments_[i];
}

template <typename FragmentType>
std::shared_ptr<FragmentType>& FragmentSet<FragmentType>::operator[](size_t i) {
  return fragments_[i];
}

template <typename FragmentType>
size_t FragmentSet<FragmentType>::Size() const {
  return fragments_.size();
}

template <typename FragmentType>
void FragmentSet<FragmentType>::Dump(JsonType &jsonType) {
  jsonType["text"] = *StrHelper::Wstr2Str(*text_);
  for (size_t i=0; i < fragments_.size(); ++i) {
    fragments_[i]->Dump(jsonType[fragments_[i]->GetCategory().c_str()][i]);
  }
}

}}}
