#pragma once

#include "../public.h"
#include "syntax/syntax_tag.h"
#include "fragment/fragment.h"
#include "fragment/fragment_set.hpp"
#include "fragment/fragment_multitag.hpp"

namespace xforce { namespace nlu { namespace basic {

class Chunk : public FragmentMultitag<SyntaxTag::Type::Val> {
 public:
  typedef FragmentMultitag<SyntaxTag::Type::Val> Super;
  typedef FragmentSet<Chunk> Set;

 public:
  inline Chunk();
  inline Chunk(SyntaxTag::Type::Val syntaxTag, size_t offset, size_t len);
  inline Chunk(const Chunk &other);
  virtual ~Chunk() {}

  bool Merge(const Fragment &other);

  const std::string& GetCategory() const;

  void Dump(JsonType &jsonType);
};

Chunk::Chunk() :
  Super() {}

Chunk::Chunk(SyntaxTag::Type::Val syntaxTag, size_t offset, size_t len) :
    Super(syntaxTag, offset, len) {}

Chunk::Chunk(const Chunk &other) :
    Super(other) {}

}}}
