#include "../pattern_item_syntax.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemSyntax::PatternItemSyntax(const basic::SyntaxTag::Type::Val &syntaxType) :
  syntaxType_(syntaxType) {}

bool PatternItemSyntax::MatchPattern(Context &context) {
  auto chunkSet = context.GetSentence().GetFeatureChunkAtOffset(context.GetCurPos());
  if (nullptr == chunkSet) {
    return false;
  }

  std::shared_ptr<basic::Chunk> theChunk = nullptr;
  size_t maxLen = 0;
  for (auto &chunk : chunkSet->GetAll()) {
    bool matched = false;
    for (auto tag : chunk->GetTags()) {
      if (tag == syntaxType_) {
        matched = true;
        break;
      }
    }

    if (!matched) {
      continue;
    }

    if (chunk->GetLen() > maxLen) {
      theChunk = chunk;
      maxLen = chunk->GetLen();
    }
  }

  if (nullptr != theChunk) {
    contentMatched_ = context.GetSentence().GetSentence().substr(
            theChunk->GetOffset(),
            theChunk->GetLen());
    return true;
  }
  return false;
}


}}}
