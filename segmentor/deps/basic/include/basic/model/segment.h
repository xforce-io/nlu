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
  inline void SetPosCtbTag(PosCtbTag::Type posCtb);

  PosTag::Type GetPosTag() const { return posTag_; }
  PosCtbTag::Type GetPosCtbTag() const { return posCtbTag_; }

  inline std::wstring GetQuery(const std::wstring &sentence) const;

  inline void operator=(const Segment &segment);

  void Dump(JsonType &jsonType);

 private:
  PosTag::Type posTag_;
  PosCtbTag::Type posCtbTag_;
};

Segment::Segment() :
  Fragment(-1, -1),
  posTag_(PosTag::kUndef),
  posCtbTag_(PosCtbTag::kUndef) {}

Segment::Segment(PosTag::Type posTag, size_t offset, size_t len) :
  Fragment(offset, len),
  posTag_(posTag),
  posCtbTag_(PosCtbTag::kUndef) {}

Segment::Segment(size_t offset, size_t len) :
  Fragment(offset, len),
  posTag_(PosTag::kUndef),
  posCtbTag_(PosCtbTag::kUndef) {}

Segment::Segment(size_t offset) :
  Fragment(offset, -1),
  posTag_(PosTag::kUndef),
  posCtbTag_(PosCtbTag::kUndef) {}

void Segment::SetPosTag(PosTag::Type posTag) {
  posTag_ = posTag;
}

void Segment::SetPosCtbTag(PosCtbTag::Type posCtb) {
  posCtbTag_ = posCtb;
}

std::wstring Segment::GetQuery(const std::wstring &sentence) const {
  return sentence.substr(offset_, len_);
}

void Segment::operator=(const Segment &segment) {
  posTag_ = segment.posTag_;
  posCtbTag_ = segment.posCtbTag_;
  offset_ = segment.offset_;
  len_ = segment.len_;
}

}}}
