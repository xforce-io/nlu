#include "../pattern_item_wordpos.h"

namespace xforce { namespace nlu { namespace milkie {

const wchar_t PatternItemWordpos::kSep == L'-'; 

PatternItemWordpos::PatternItemWordpos(const std::wstring &patternStr) {
  regex_ = CreatePattern_(patternStr);
}

bool PatternItemWordpos::MatchPattern(const Context &context) {
  auto featureWordposes = context.GetSentence().GetFeatureSegmentsAtOffset(context.GetCurPos());
  if (featureWordposes.get() == NULL) {
    return false;
  }

  std::wstringstream ss;
  for (auto segment : *featureWordposes) {
    ss << segment.GetPos() << kSep;
  }

  std::wcmatch wcm;
  if (std::regex_search(ss.str(), wcm, ss.str())) { 
    const std::wstring &matched = wcm[0].str();
    if (ss.str().substr(0, matched.length()) == matched) {
      Wstrings items;
      StrHelper::SplitStr(matched, kSep, items);
      contentMatched_ = "";
      for (size_t i=0; i < items.length(); ++i) {
        contentMatched_ += featureWordposes[i].GetQuery(
            context.GetSentence().GetSentence());
      }
      return true;
    }
  }
  return false;
}

std::wregex* PatternItemWordpos::CreatePattern_(const std::wstring &patternStr) {
  std::wstring tmpPattern = patternStr;

  size_t cntSep = 0;
  for (size_t i=0; i < patternStr.length(); ++i) {
    if (kSep == patternStr[i]) {
      ++cntSep;
    }
  }

  if (0 == cntSep) {
    tmpPattern.append(1, kSep);
  }
  return new std::wregex(tmpPattern);
}

PatternItemWordpos::~PatternItemWordpos() {
  XFC_DELETE(regex_)
}

}}}
