#pragma once

#include "public.h"
#include "pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItemSyntax : public PatternItem {
 public:
  explicit PatternItemSyntax(const basic::SyntaxTag::Type::Val &syntaxType);
  virtual ~PatternItemSyntax() {}

  bool MatchPattern(Context &context) final;

 private:
  std::shared_ptr<basic::Chunk> GetLongestMatch_(
          const basic::Chunk::Set &chunkSet,
          const std::unordered_set<basic::SyntaxTag::Type::Val > &syntaxSet);

 private:
  basic::SyntaxTag::Type::Val syntaxType_;
};

}}}
