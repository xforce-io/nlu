#pragma once

#include "../../public.h"
#include "../confidence.h"

namespace xforce { namespace nlu { namespace basic {

class Fragment {
 public:
  typedef std::vector<std::shared_ptr<Fragment>> Vec;
  typedef std::list<std::shared_ptr<Fragment>> List;

 public:
  struct Compare {
      bool operator() (
              const std::shared_ptr<Fragment> &lhs,
              const std::shared_ptr<Fragment> &rhs) const {
        return lhs->GetOffset() < rhs->GetOffset();
      }
  };

 public:
  inline Fragment();
  inline Fragment(size_t offset, size_t len);
  inline Fragment(const Fragment &other);
  virtual ~Fragment();

  inline void SetStr(const std::wstring &str);
  inline void SetStrFromSentence(const std::wstring &sentence);
  inline void SetOffset(size_t offset);
  inline void SetLen(size_t len);
  inline void SetConfidence(const Confidence &confidence);
  inline void SetStrategy(uint32_t strategy);
  inline Fragment& operator=(const Fragment &other);

  virtual const std::string& GetCategory() const = 0;
  const Fragment* GetFather() const { return father_; }
  const std::wstring* GetStr() const { return str_; }
  inline const std::wstring GetStrFromSentence(const std::wstring &sentence);
  size_t GetOffset() const { return offset_; }
  size_t GetLen() const { return len_; }
  size_t GetBegin() const { return offset_; }
  inline size_t GetEnd() const;
  Confidence GetConfidence() const { return confidence_; }
  inline uint32_t GetStrategy() const { return strategy_; }

  inline bool Intersect(const Fragment &fragment) const;

  virtual void Dump(JsonType &jsonType);

 protected:
  Fragment *father_;
  std::wstring *str_;

  size_t offset_;
  size_t len_;
  Confidence confidence_;
  uint32_t strategy_;
};

Fragment::Fragment() :
  father_(nullptr),
  str_(nullptr),
  strategy_(0) {}

Fragment::Fragment(size_t offset, size_t len) :
  father_(nullptr),
  str_(nullptr),
  offset_(offset),
  len_(len),
  strategy_(0) {}

Fragment::Fragment(const Fragment &other) {
  *this = other;
}

void Fragment::SetStr(const std::wstring &str) {
  str_ = new std::wstring(str);
}

void Fragment::SetStrFromSentence(const std::wstring &sentence) {
  str_ = new std::wstring(sentence.substr(offset_, len_));
}

void Fragment::SetOffset(size_t offset) {
  offset_ = offset;
}

void Fragment::SetLen(size_t len) {
  len_ = len;
}

void Fragment::SetConfidence(const Confidence &confidence) {
  confidence_ = confidence;
}

void Fragment::SetStrategy(uint32_t strategy) {
  strategy_ = strategy;
}

Fragment& Fragment::operator=(const Fragment &other) {
  father_ = other.father_;
  if (nullptr != str_) {
    XFC_DELETE(str_)
  }

  if (nullptr != other.str_) {
    str_ = new std::wstring(*(other.str_));
  }

  offset_ = other.offset_;
  len_= other.len_;
  confidence_ = other.confidence_;
  strategy_ = other.strategy_;
  return *this;
}

const std::wstring Fragment::GetStrFromSentence(const std::wstring &sentence) {
  return sentence.substr(offset_, len_);
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
