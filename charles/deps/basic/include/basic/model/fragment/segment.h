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

  DistRes Distance(const Fragment &arg0, const Fragment &arg1) const;

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

typename Fragment::DistRes
Segment::Distance(const Fragment &arg0, const Fragment &arg1) const {
  if (arg0.GetCategory() != Category::kSegment ||
      arg1.GetCategory() != Category::kSegment) {
    return Fragment::kUnknown;
  }

  PosTag::Class::Val classThis = GetClassOfPosTags();
  PosTag::Class::Val classArg0 = ((const Segment&)arg0).GetClassOfPosTags();
  PosTag::Class::Val classArg1 = ((const Segment&)arg1).GetClassOfPosTags();
  if (classThis != PosTag::Class::kUndef) {
    if (classThis == classArg0 && classThis != classArg1) {
      return Fragment::kArg0;
    } else if (classThis != classArg0 && classThis == classArg1) {
      return Fragment::kArg1;
    }
  }
  return Fragment::kUnknown;
}

}}}
