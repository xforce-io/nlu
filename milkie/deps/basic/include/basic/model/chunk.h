#pragma once

#include "../public.h"
#include "syntax/syntax_tag.h"
#include "fragment/fragment.h"
#include "fragment/fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

class Chunk : public Fragment {
 public:
  typedef Fragment Super;
  typedef FragmentSet<Chunk> Set;

 public:
  inline Chunk();
  inline Chunk(SyntaxTag::Type syntaxTag, size_t offset, size_t len);
  virtual ~Chunk();

  inline void SetStr(const std::wstring &str);
  inline void SetSyntaxTag(SyntaxTag::Type syntaxTag);

  const std::wstring* GetStr() const { return str_; }
  SyntaxTag::Type GetSyntaxTag() const { return syntaxTag_; }

  void Dump(JsonType &jsonType);

 private:
  std::wstring *str_;
  SyntaxTag::Type syntaxTag_;
};

Chunk::Chunk() :
  Fragment(-1, -1),
  str_(nullptr),
  syntaxTag_(SyntaxTag::kUndef) {}

Chunk::Chunk(SyntaxTag::Type syntaxTag, size_t offset, size_t len) :
  Fragment(offset, len),
  str_(nullptr),
  syntaxTag_(syntaxTag) {}

void Chunk::SetStr(const std::wstring &str) {
  str_ = new std::wstring(str);
}

void Chunk::SetSyntaxTag(SyntaxTag::Type syntaxTag) {
  syntaxTag_ = syntaxTag;
}

}}}
