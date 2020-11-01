#include "../pattern_item_reg.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

PatternItemReg::PatternItemReg(const std::wstring &patternStr) {
  std::wstring patternToApply = patternStr;
  ReplaceFamousPattern_(patternToApply);
  regex_ = CreatePattern_(patternToApply);
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

void PatternItemReg::ReplaceFamousPattern_(std::wstring &patternStr) {
  std::unordered_map<std::wstring, std::wstring> patterns{
    {L"_NUM_", L"[0-9]"}, 
    {L"_NUM_WITH_CHN_", L"[0-9一二三四五六七八九十零]"}, 
  };

  for (auto &pair : patterns) {
    ReplaceSingleFamousPattern_(
        pair.first, 
        pair.second, 
        patternStr);
  }
}

void PatternItemReg::ReplaceSingleFamousPattern_(
    const std::wstring &key,
    const std::wstring &val,
    std::wstring &patternStr) {
  auto pos = patternStr.find(key);
  if (std::wstring::npos != pos) {
    patternStr.replace(pos, pos+key.length(), val);
  }
}

std::wregex* PatternItemReg::CreatePattern_(const std::wstring &patternStr) {
  return new std::wregex(patternStr);
}

}}}
