#include "../pattern_item_syntax.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemSyntax::PatternItemSyntax(const basic::SyntaxTag::Type::Val &syntaxType) :
  syntaxType_(syntaxType) {}

bool PatternItemSyntax::MatchPattern(Context &context) {
  ssize_t originOffset = context.GetCurPos();
  ssize_t offset = context.GetCurPos();
  std::unordered_set<basic::SyntaxTag::Type::Val> syntaxSetToMatch;
  syntaxSetToMatch.insert(syntaxType_);

  std::unordered_set<basic::SyntaxTag::Type::Val> syntaxSetToIgnore;
  do {
    auto chunkSet = context.GetSentence().GetFeatureChunkAtOffset(offset);
    if (nullptr == chunkSet) {
      return false;
    }

    auto theChunk = GetLongestMatch_(*chunkSet, syntaxSetToMatch);
    if (nullptr != theChunk) {
      contentMatched_ = context.GetSentence().GetSentence().substr(
              originOffset,
              theChunk->GetEnd() - originOffset);
      return true;
    } else {
      theChunk = GetLongestMatch_(*chunkSet, syntaxSetToIgnore);
      if (nullptr != theChunk) {
        offset += theChunk->GetLen();
      } else {
        return false;
      }
    }
  } while(offset < context.GetSentence().GetSentence().length());
  return false;
}

std::shared_ptr<basic::Chunk> PatternItemSyntax::GetLongestMatch_(
        const basic::Chunk::Set &chunkSet,
        const std::unordered_set<basic::SyntaxTag::Type::Val> &syntaxSet) {
  std::shared_ptr<basic::Chunk> theChunk = nullptr;
  size_t maxLen = 0;
  for (auto &chunk : chunkSet.GetAll()) {
    bool matched = false;
    for (auto tag : chunk->GetTags()) {
      if (syntaxSet.find(tag) != syntaxSet.end()) {
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
  return theChunk;
}


}}}
