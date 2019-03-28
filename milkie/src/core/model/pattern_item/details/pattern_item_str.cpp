#include "../pattern_item_str.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemStr::PatternItemStr(const std::wstring &patternStr) :
    patternStr_(patternStr) {}

bool PatternItemStr::MatchPattern(Context &context) {
  if (context.GetSentence().GetFeatureContent(context.GetCurPos()).find(patternStr_) == 0) {
    contentMatched_ = patternStr_;
    return true;
  }
  return false;
}

}}}
