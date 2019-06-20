#include "../pattern_item_syntax.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemSyntax::PatternItemSyntax(const basic::SyntaxTag::Type &syntaxType) :
  syntaxType_(syntaxType) {}

bool PatternItemSyntax::MatchPattern(Context &context) {
  auto featureChunk = context.GetSentence().GetFeatureChunkAtOffset(context.GetCurPos());
  if (nullptr == featureChunk) {
    return false;
  }

  if (featureChunk->GetSyntaxTag() == syntaxType_) {
    return false;
  }

  contentMatched_ = context.GetSentence().GetSentence().substr(
          featureChunk->GetOffset(),
          featureChunk->GetLen());
  return true;
}


}}}
