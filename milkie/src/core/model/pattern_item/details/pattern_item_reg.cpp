#include "../pattern_item_reg.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemReg::PatternItemReg(const std::wstring &patternStr) {
  regex_ = CreatePattern_(patternStr);
}

PatternItemReg::~PatternItemReg() {
  XFC_DELETE(regex_)
}

bool PatternItemReg::MatchPattern(Context &context) {
  auto featureContent = context.GetSentence().GetFeatureContent(context.GetCurPos());
  std::wcmatch wcm;
  if (std::regex_search(featureContent.c_str(), wcm, *regex_)) {
    const std::wstring &matched = wcm[0].str();
    if (featureContent.substr(0, matched.length()) == matched) {
      contentMatched_ = matched;
      return true;
    }
  }
  return false;
}

std::wregex* PatternItemReg::CreatePattern_(const std::wstring &patternStr) {
  return new std::wregex(patternStr);
}

}}}