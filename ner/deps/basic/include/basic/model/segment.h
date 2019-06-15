#pragma once

#include "../public.h"
#include "pos/pos_tag.h"
#include "pos_ctb/pos_ctb_tag.h"
#include "fragment/fragment.h"
#include "fragment/fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

class Segment : public Fragment {
 public:
  typedef Fragment Super;
  typedef FragmentSet<Segment> Set;

 public:
  inline Segment();
  inline Segment(PosTag::Type::Val posTag, size_t offset, size_t len);
  inline Segment(size_t offset, size_t len);
  inline Segment(size_t offset);
  inline Segment(const Segment &other);
  virtual ~Segment() {}

  inline void SetPosTag(PosTag::Type::Val posTag);
  inline void AddPosTag(PosTag::Type::Val posTag);
  inline void RemovePosTag(PosTag::Type::Val posTag);

  const std::string& GetCategory() const;
  size_t SizePosTags() const { return posTags_.size(); }
  const std::vector<PosTag::Type::Val>& GetPosTags() const { return posTags_; }
  std::vector<PosTag::Type::Val>& GetPosTags() { return posTags_; }
  inline PosTag::Type::Val GetPosTag() const;
  inline PosTag::Class::Val GetClassOfPosTags() const;
  inline bool ContainPosTag(PosTag::Type::Val posTag);

  inline std::wstring GetQuery(const std::wstring &sentence) const;

  void Dump(JsonType &jsonType);

 private:
  std::vector<PosTag::Type::Val> posTags_;
};

Segment::Segment() :
    Fragment(-1, -1) {}

Segment::Segment(PosTag::Type::Val posTag, size_t offset, size_t len) :
    Fragment(offset, len) {
  SetPosTag(posTag);
}

Segment::Segment(size_t offset, size_t len) :
    Fragment(offset, len) {}

Segment::Segment(size_t offset) :
    Fragment(offset, -1) {}

Segment::Segment(const Segment &other) :
    Super(other) {
  posTags_ = other.posTags_;
}

void Segment::SetPosTag(PosTag::Type::Val posTag) {
  posTags_.clear();
  posTags_.push_back(posTag);
}

void Segment::AddPosTag(PosTag::Type::Val posTag) {
  for (auto &singlePosTag : posTags_) {
    if (singlePosTag == posTag) {
      return;
    }
  }
  posTags_.push_back(posTag);
}

void Segment::RemovePosTag(PosTag::Type::Val posTag) {
  for (auto iter = posTags_.begin(); iter != posTags_.end(); ++iter) {
    if (*iter == posTag) {
      posTags_.erase(iter);
      return;
    }
  }
}

PosTag::Type::Val Segment::GetPosTag() const {
  return posTags_.size() == 1 ? posTags_[0] : PosTag::Type::kUndef;
}

PosTag::Class::Val Segment::GetClassOfPosTags() const {
  PosTag::Class::Val result = PosTag::Class::kUndef;
  for (auto &posTag : posTags_) {
    auto curPosTag = PosTag::GetClass(posTag);
    if (PosTag::Class::kUndef == curPosTag ||
        (PosTag::Class::kUndef != result &&
        curPosTag != result)) {
      return PosTag::Class::kUndef;
    }
    result = curPosTag;
  }
  return result;
}

bool Segment::ContainPosTag(PosTag::Type::Val posTag) {
  for (auto &singlePosTag : posTags_) {
    if (singlePosTag == posTag) {
      return true;
    }
  }
  return false;
}

std::wstring Segment::GetQuery(const std::wstring &sentence) const {
  return sentence.substr(offset_, len_);
}

}}}
