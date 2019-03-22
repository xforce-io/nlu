#pragma once

#include "../../public.h"
#include "fragment.h"

namespace xforce { namespace nlu { namespace basic {

template <typename FragmentType>
class FragmentSet {
 public:
  explicit FragmentSet(const std::wstring &text);
  virtual ~FragmentSet();

  virtual void Add(std::shared_ptr<FragmentType> fragment);
  void Add(const FragmentType &fragment);

  inline const std::vector<std::shared_ptr<FragmentType>> GetAll() const;

  inline const std::shared_ptr<FragmentType>& operator[](size_t i) const;
  inline std::shared_ptr<FragmentType>& operator[](size_t i);

  inline size_t Size() const;

 protected:
  const std::wstring *text_;

  std::vector<std::shared_ptr<FragmentType>> fragments_;
};

template <typename FragmentType>
FragmentSet<FragmentType>::FragmentSet(const std::wstring &text) :
    text_(&text) {}

template <typename FragmentType>
FragmentSet<FragmentType>::~FragmentSet() {
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

}}}
