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

  inline void SetSyntaxTag(SyntaxTag::Type syntaxTag);

  const std::string& GetCategory() const;
  SyntaxTag::Type GetSyntaxTag() const { return syntaxTag_; }

  inline void operator=(const Chunk &other);

  void Dump(JsonType &jsonType);

 private:
  SyntaxTag::Type syntaxTag_;
};

Chunk::Chunk() :
  Fragment(-1, -1),
  syntaxTag_(SyntaxTag::kUndef) {}

Chunk::Chunk(SyntaxTag::Type syntaxTag, size_t offset, size_t len) :
  Fragment(offset, len),
  syntaxTag_(syntaxTag) {}

void Chunk::SetSyntaxTag(SyntaxTag::Type syntaxTag) {
  syntaxTag_ = syntaxTag;
}

void Chunk::operator=(const Chunk &other) {
  Super::operator=(other);
  syntaxTag_ = other.syntaxTag_;
}

}}}
