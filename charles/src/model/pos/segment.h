#pragma once

#include "public.h"
#include "pos.h"

namespace xforce { namespace nlu { namespace charles {

class Segment {
 public:
  inline Segment(Pos::Type pos, size_t offset, size_t len);
  inline Segment(size_t offset, size_t len);

  inline void SetPos(Pos::Type pos);

  Pos::Type GetPos() const { return pos_; }
  size_t GetOffset() const { return offset_; }
  size_t GetLen() const { return len_; }

 private:
  Pos::Type pos_;
  size_t offset_;
  size_t len_;
};

Segment::Segment(Pos::Type pos, size_t offset, size_t len) :
  pos_(pos),
  offset_(offset),
  len_(len) {}

Segment::Segment(size_t offset, size_t len) :
  offset_(offset),
  len_(len) {}

void Segment::SetPos(Pos::Type pos) {
  pos_ = pos;
}

}}}
