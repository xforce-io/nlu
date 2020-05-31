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

  inline ssize_t Distance(const Fragment &other) const;

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
  for (auto &tag : tags_) {
    auto curTag = PosTag::GetClass(tag);
    if (PosTag::Class::kUndef == curTag ||
        (PosTag::Class::kUndef != result &&
         curTag != result)) {
      return PosTag::Class::kUndef;
    }
    result = curTag;
  }
  return result;
}

ssize_t Segment::Distance(const Fragment &other) const {
  if (other.GetCategory() != Category::kSegment) {
    return -1;
  }

  PosTag::Class::Val classThis = GetClassOfPosTags();
  PosTag::Class::Val classOther = ((const Segment&)other).GetClassOfPosTags();
  if (classThis != PosTag::Class::kUndef && classThis == classOther) {
    return 1;
  }
  return -1;
}

}}}
