#include "../pattern_item_syntax.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemSyntax::PatternItemSyntax(const std::wstring &pattern) :
  pattern_(pattern) {}

PatternItemSyntax::~PatternItemSyntax() {

}

bool PatternItemSyntax::MatchPattern(Context &context) {
  auto featureChunk = context.GetSentence().GetFeature
}


}}}
