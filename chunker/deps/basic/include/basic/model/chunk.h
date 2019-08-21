#pragma once

#include "../public.h"
#include "syntax/syntax_tag.h"
#include "fragment/fragment.h"
#include "fragment/fragment_set.hpp"
#include "fragment/fragment_multitag.hpp"

namespace xforce { namespace nlu { namespace basic {

class Chunk : public FragmentMultitag<SyntaxTag::Type> {
 public:
  enum DescDir {
    kNone,
    kLeft,
    kRight,
    kBoth,
  };

 public:
  typedef FragmentMultitag<SyntaxTag::Type> Super;
  typedef FragmentSet<Chunk> Set;

 public:
  inline Chunk();
  inline Chunk(
          SyntaxTag::Type::Val syntaxTag,
          size_t offset,
          size_t len,
          uint32_t strategy=0);

  inline Chunk(const Chunk &other);
  virtual ~Chunk() {}

  inline void SetDescDir(DescDir descDir);
  inline DescDir GetDescDir() const;

  virtual const std::string& GetCategory() const;

  virtual void Dump(JsonType &jsonType);

 private:
  DescDir descDir_;
};

Chunk::Chunk() :
  Super() {}

Chunk::Chunk(
        SyntaxTag::Type::Val syntaxTag,
        size_t offset,
        size_t len,
        uint32_t strategy) :
    Super(syntaxTag, offset, len, strategy) {}

Chunk::Chunk(const Chunk &other) :
    Super(SCAST<const Super&>(other)) {}

void Chunk::SetDescDir(DescDir descDir) {
  descDir_ = descDir;
}

Chunk::DescDir Chunk::GetDescDir() const {
  return descDir_;
}

}}}
