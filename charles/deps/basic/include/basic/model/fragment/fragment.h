#pragma once

#include "../../public.h"
#include "../confidence.h"

namespace xforce { namespace nlu { namespace basic {

class Fragment {
 public:
  typedef std::vector<std::shared_ptr<Fragment>> Vec;
  typedef std::list<std::shared_ptr<Fragment>> List;

 public:
  inline Fragment();
  inline Fragment(size_t offset, size_t len);

  inline void SetOffset(size_t offset);
  inline void SetLen(size_t len);
  inline void SetConfidence(const Confidence &confidence);

  const Fragment* GetFather() const { return father_; }
  size_t GetOffset() const { return offset_; }
  size_t GetLen() const { return len_; }
  size_t GetBegin() const { return offset_; }
  inline size_t GetEnd() const;
  Confidence GetConfidence() const { return confidence_; }

  inline bool Intersect(const Fragment &fragment) const;

 protected:
  Fragment *father_;

  size_t offset_;
  size_t len_;
  Confidence confidence_;
};

Fragment::Fragment() :
  father_(nullptr) {}

Fragment::Fragment(size_t offset, size_t len) :
  father_(nullptr),
  offset_(offset),
  len_(len) {}

void Fragment::SetOffset(size_t offset) {
  offset_ = offset;
}

void Fragment::SetLen(size_t len) {
  len_ = len;
}

void Fragment::SetConfidence(const Confidence &confidence) {
  confidence_ = confidence;
}

size_t Fragment::GetEnd() const {
  return offset_ + len_;
}

bool Fragment::Intersect(const Fragment &fragment) const {
  return father_ == fragment.GetFather() &&
      fragment.GetEnd() > GetBegin() &&
      fragment.GetBegin() < GetEnd();
}

}}}
