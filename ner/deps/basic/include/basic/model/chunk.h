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
  struct Compare {
    bool operator() (
            const std::shared_ptr<Chunk> &lhs,
            const std::shared_ptr<Chunk> &rhs) const {
      return lhs->GetOffset() < rhs->GetOffset() ||
             (lhs->GetOffset() == rhs->GetOffset() &&
              lhs->GetLen() < rhs->GetLen()) ||
             (lhs->GetOffset() == rhs->GetOffset() &&
              lhs->GetLen() == rhs->GetLen() &&
              lhs->GetSyntaxTag() < rhs->GetSyntaxTag());
    }
  };

 public:
  inline Chunk();
  inline Chunk(SyntaxTag::Type syntaxTag, size_t offset, size_t len);
  inline Chunk(const Chunk &other);
  virtual ~Chunk();

  inline void SetSyntaxTag(SyntaxTag::Type syntaxTag);

  const std::string& GetCategory() const;
  SyntaxTag::Type GetSyntaxTag() const { return syntaxTag_; }

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

Chunk::Chunk(const Chunk &other) :
    Super(other) {
  syntaxTag_ = other.syntaxTag_;
}

void Chunk::SetSyntaxTag(SyntaxTag::Type syntaxTag) {
  syntaxTag_ = syntaxTag;
}

}}}
