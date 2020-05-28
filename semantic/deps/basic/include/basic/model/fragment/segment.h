#pragma once

#include "../../public.h"
#include "../pos/pos_tag.h"
#include "../pos_ctb/pos_ctb_tag.h"
#include "fragment.h"
#include "fragment_set.hpp"
#include "fragment_multitag.hpp"

namespace xforce { namespace nlu { namespace basic {

class Segment : public FragmentMultitag<PosTag::Type> {
 public:
  typedef FragmentMultitag<PosTag::Type> Super;
  typedef FragmentSet<Segment> Set;

 public:
  inline Segment();
  inline Segment(PosTag::Type::Val posTag, size_t offset, size_t len);
  inline Segment(size_t offset, size_t len);
  inline Segment(size_t offset);
  inline Segment(const Segment &other);
  virtual ~Segment() {}

  inline void AddTag(typename PosTag::Type::Val tag);

  typename Fragment::Category GetCategory() const { return kSegment; }
  inline PosTag::Class::Val GetClassOfPosTags() const;

  virtual void Dump(JsonType &jsonType) const;
};

Segment::Segment() :
    Super() {}

Segment::Segment(PosTag::Type::Val posTag, size_t offset, size_t len) :
    Super(posTag, offset, len) {}

Segment::Segment(size_t offset, size_t len) :
    Super(offset, len) {}

Segment::Segment(size_t offset) :
    Super(offset) {}

Segment::Segment(const Segment &other) :
    Super(SCAST<const Super&>(other)) {}

void Segment::AddTag(typename PosTag::Type::Val tag) {
  for (auto &singleTag : tags_) {
    if (singleTag == tag ||
        (singleTag == PosTag::Type::kN && tag == PosTag::Type::kVn) ||
        (singleTag == PosTag::Type::kVn && tag == PosTag::Type::kN)) {
      return;
    }
  }
  tags_.push_back(tag);
}

PosTag::Class::Val Segment::GetClassOfPosTags() const {
  PosTag::Class::Val result = PosTag::Class::kUndef;
  for (auto &posTag : tags_) {
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

}}}
