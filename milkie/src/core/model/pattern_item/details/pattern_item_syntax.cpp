#include "../pattern_item_syntax.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemSyntax::PatternItemSyntax(const std::wstring &pattern) :
  pattern_(pattern) {}

bool PatternItemSyntax::MatchPattern(Context &context) {
  auto featureChunk = context.GetSentence().GetFeatureChunksFromOffset(context.GetCurPos());
  if (nullptr == featureChunk) {
    return false;
  }

  size_t maxLen = 0;
  std::shared_ptr<basic::Chunk> matchedChunk;
  for (auto &chunk : featureChunk->GetAll()) {
    if (*(chunk->GetStr()) == pattern_ &&
        chunk->GetOffset() == context.GetCurPos() &&
        chunk->GetLen() > maxLen) {
      maxLen = chunk->GetLen();
      matchedChunk = chunk;
    }
  }

  if (maxLen != 0) {
    contentMatched_ = context.GetSentence().GetSentence().substr(
            matchedChunk->GetOffset(),
            matchedChunk->GetLen());
    return true;
  } else {
    return false;
  }
}


}}}
