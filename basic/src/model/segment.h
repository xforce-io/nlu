#pragma once

#include "../public.h"
#include "pos/pos.h"
#include "fragment/fragment.h"

namespace xforce { namespace nlu { namespace basic {

class Segment : public Fragment {
 public:
  typedef Fragment Super;
  typedef std::vector<Segment> Vector;

 public:
  inline Segment();
  inline Segment(Pos::Type pos, size_t offset, size_t len);
  inline Segment(size_t offset, size_t len);
  inline Segment(size_t offset);

  inline void SetPos(Pos::Type pos);
  Pos::Type GetPos() const { return pos_; }

  inline std::wstring GetQuery(const std::wstring &sentence) const;

  inline void operator=(const Segment &segment);

  void Dump(JsonType &jsonType);

 private:
  Pos::Type pos_;
};

Segment::Segment() :
  pos_(Pos::kUndef),
  Fragment(-1, -1) {}

Segment::Segment(Pos::Type pos, size_t offset, size_t len) :
  pos_(pos),
  Fragment(offset, len) {}

Segment::Segment(size_t offset, size_t len) :
  pos_(Pos::kUndef),
  Fragment(offset, len) {}

Segment::Segment(size_t offset) :
  pos_(Pos::kUndef),
  Fragment(offset, -1) {}

std::wstring Segment::GetQuery(const std::wstring &sentence) const {
  return sentence.substr(offset_, len_);
}

void Segment::operator=(const Segment &segment) {
  pos_ = segment.pos_;
  offset_ = segment.offset_;
  len_ = segment.len_;
}

}}}
