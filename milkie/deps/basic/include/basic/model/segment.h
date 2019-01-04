#pragma once

#include "public.h"
#include "pos/pos.h"

namespace xforce { namespace nlu { namespace basic {

class Segment {
 public:
  inline Segment();
  inline Segment(Pos::Type pos, size_t offset, size_t len);
  inline Segment(size_t offset, size_t len);
  inline Segment(size_t offset);

  inline void SetPos(Pos::Type pos);
  inline void SetLen(size_t len);

  Pos::Type GetPos() const { return pos_; }
  size_t GetOffset() const { return offset_; }
  size_t GetLen() const { return len_; }
  inline std::wstring GetQuery(const std::wstring &query) const;

  inline void operator=(const Segment &segment);

  void Dump(JsonType &jsonType);


 private:
  Pos::Type pos_;
  size_t offset_;
  size_t len_;
};

typedef std::vector<Segment> Segments;

Segment::Segment() :
  pos_(Pos::kUndef),
  offset_(-1),
  len_(-1) {}

Segment::Segment(Pos::Type pos, size_t offset, size_t len) :
  pos_(pos),
  offset_(offset),
  len_(len) {}

Segment::Segment(size_t offset, size_t len) :
  pos_(Pos::kUndef),
  offset_(offset),
  len_(len) {}

Segment::Segment(size_t offset) :
  pos_(Pos::kUndef),
  offset_(offset),
  len_(-1) {}

void Segment::SetPos(Pos::Type pos) {
  pos_ = pos;
}

void Segment::SetLen(size_t len) {
  len_ = len;
}

std::wstring Segment::GetQuery(const std::wstring &query) const {
  return query.substr(offset_, len_);
}

void Segment::operator=(const Segment &segment) {
  pos_ = segment.pos_;
  offset_ = segment.offset_;
  len_ = segment.len_;
}


}}}
