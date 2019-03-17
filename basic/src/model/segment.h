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
  virtual ~Segment();

  inline void SetStr(const std::wstring &str);
  inline void SetStrFromSentence(const std::wstring &sentence);
  inline void SetPos(Pos::Type pos);

  const std::wstring* GetStr() const { return str_; }
  Pos::Type GetPos() const { return pos_; }

  inline std::wstring GetQuery(const std::wstring &sentence) const;

  inline void operator=(const Segment &segment);

  void Dump(JsonType &jsonType);

 private:
  std::wstring *str_;
  Pos::Type pos_;
};

Segment::Segment() :
  Fragment(-1, -1),
  str_(nullptr),
  pos_(Pos::kUndef) {}

Segment::Segment(Pos::Type pos, size_t offset, size_t len) :
  Fragment(offset, len),
  str_(nullptr),
  pos_(pos) {}

Segment::Segment(size_t offset, size_t len) :
  Fragment(offset, len),
  str_(nullptr),
  pos_(Pos::kUndef) {}

Segment::Segment(size_t offset) :
  Fragment(offset, -1),
  str_(nullptr),
  pos_(Pos::kUndef) {}

void Segment::SetStr(const std::wstring &str) {
  str_ = new std::wstring(str);
}

void Segment::SetStrFromSentence(const std::wstring &sentence) {
  str_ = new std::wstring(sentence.substr(offset_, len_));
}

void Segment::SetPos(Pos::Type pos) {
  pos_ = pos;
}

std::wstring Segment::GetQuery(const std::wstring &sentence) const {
  return sentence.substr(offset_, len_);
}

void Segment::operator=(const Segment &segment) {
  pos_ = segment.pos_;
  offset_ = segment.offset_;
  len_ = segment.len_;
}

}}}
