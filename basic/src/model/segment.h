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
  inline Segment(PosTag::Type posTag, size_t offset, size_t len);
  inline Segment(size_t offset, size_t len);
  inline Segment(size_t offset);
  virtual ~Segment() {}

  inline void SetPosTag(PosTag::Type posTag);
  inline void AddPosTag(PosTag::Type posTag);
  const std::vector<PosTag::Type> GetPosTags() const { return posTags_; }

  inline std::wstring GetQuery(const std::wstring &sentence) const;

  inline void operator=(const Segment &segment);

  void Dump(JsonType &jsonType);

 private:
  std::vector<PosTag::Type> posTags_;
};

Segment::Segment() :
  Fragment(-1, -1) {}

Segment::Segment(PosTag::Type posTag, size_t offset, size_t len) :
  Fragment(offset, len) {}

Segment::Segment(size_t offset, size_t len) :
  Fragment(offset, len) {}

Segment::Segment(size_t offset) :
  Fragment(offset, -1) {}

void Segment::SetPosTag(PosTag::Type posTag) {
  posTags_.clear();
  posTags_.push_back(posTag);
}

void Segment::AddPosTag(PosTag::Type posTag) {
  posTags_.push_back(posTag);
}

std::wstring Segment::GetQuery(const std::wstring &sentence) const {
  return sentence.substr(offset_, len_);
}

void Segment::operator=(const Segment &segment) {
  posTags_ = segment.posTags_;
  offset_ = segment.offset_;
  len_ = segment.len_;
}

}}}
