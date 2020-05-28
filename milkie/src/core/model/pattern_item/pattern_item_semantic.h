#pragma once

#include "public.h"
#include "pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItemSemantic : public PatternItem {
 public:
  explicit PatternItemSemantic(const basic::SemanticUnit::Type::Val &semanticType);
  virtual ~PatternItemSemantic() {}

  bool MatchPattern(Context &context) final;

 private:
  std::shared_ptr<basic::SemanticUnit> GetLongestMatch_(
          const basic::Chunk::Set &chunkSet,
          const std::unordered_set<basic::SemanticUnit::Type::Val> &semanticUnits);

 private:
  basic::SemanticUnit::Type::Val semanticType_;
};

}}}