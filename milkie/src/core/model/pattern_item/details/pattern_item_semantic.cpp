#include "../pattern_item_semantic.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemSemantic::PatternItemSemantic(const basic::SemanticUnit::Type::Val &semanticType) :
  semanticType_(semanticType) {}

bool PatternItemSemantic::MatchPattern(Context &context) {
  std::shared_ptr<basic::Chunk::Set> chunkSet;
  ssize_t originOffset = context.GetCurPos();
  ssize_t offset = context.GetCurPos();
  std::unordered_set<basic::SemanticUnit::Type::Val> semanticUnitTypesToMatch;
  semanticUnitTypesToMatch.insert(semanticType_);

  std::unordered_set<basic::SemanticUnit::Type::Val> semanticUnitTypesToIgnore;
  do {
    chunkSet = context.GetSentence().GetFeatureChunkAtOffset(offset);
    if (nullptr == chunkSet) {
      return false;
    }

    auto theChunk = GetLongestMatch_(*chunkSet, semanticUnitTypesToMatch);
    if (nullptr != theChunk) {
      contentMatched_ = context.GetSentence().GetSentence().substr(
              originOffset,
              theChunk->GetEnd() - originOffset);
      return true;
    } else {
      theChunk = GetLongestMatch_(*chunkSet, semanticUnitTypesToIgnore);
      if (nullptr != theChunk) {
        offset += theChunk->GetLen();
      } else {
        return false;
      }
    }
  } while (offset < context.GetSentence().GetSentence().length());
  return false;
}

std::shared_ptr<basic::Chunk> PatternItemSemantic::GetLongestMatch_(
        const basic::Chunk::Set &chunkSet,
        const std::unordered_set<basic::SemanticUnit::Type::Val> &semanticUnits) {
  std::shared_ptr<basic::Chunk> theChunk = nullptr;
  size_t maxLen = 0;
  for (auto &chunk : chunkSet.GetAll()) {
    auto tag = chunk->GetSemanticUnit()->GetType();
    if (semanticUnits.find(tag) != semanticUnits.end() &&
        chunk->GetLen() > maxLen) {
      theChunk = chunk;
      maxLen = chunk->GetLen();
    }
  }
  return theChunk;
}

}}}
