#include "../pattern_item_wordpos.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

const wchar_t PatternItemWordpos::kSep = L'-';

PatternItemWordpos::PatternItemWordpos(const std::wstring &patternStr) {
  regex_ = CreatePattern_(patternStr);
}

PatternItemWordpos::~PatternItemWordpos() {
  XFC_DELETE(regex_)
}

bool PatternItemWordpos::MatchPattern(Context &context) {
  auto featureWordposes = context.GetSentence().GetFeatureSegmentsFromOffset(context.GetCurPos());
  if (nullptr == featureWordposes) {
    return false;
  }

  size_t numMulti = 0;
  size_t sizeMulti = 1;
  for (auto &segment : featureWordposes->GetAll()) {
    if (segment->GetTags().size() > 1) {
      ++numMulti;
      sizeMulti = segment->GetTags().size();
    }
  }

  std::wcmatch wcm;
  std::wstring patternToMatch;
  std::wstring matched;
  if (0==numMulti) {
    std::wstringstream ss;
    for (auto &segment : featureWordposes->GetAll()) {
      ss << basic::PosTag::Str(segment->GetTag()) << kSep;
    }

    patternToMatch = ss.str();
    if (!std::regex_search(patternToMatch.c_str(), wcm, *regex_)) {
      return false;
    }

    const std::wstring &tmpMatched = wcm[0].str();
    if (patternToMatch.substr(0, tmpMatched.length()) != tmpMatched) {
      return false;
    }
    matched = tmpMatched;
  } else if (1==numMulti) {
    std::vector<std::wstringstream> multiSs;
    multiSs.resize(sizeMulti);
    for (auto &segment : featureWordposes->GetAll()) {
      if (segment->GetTags().size() == 1) {
        for (auto &ss : multiSs) {
          ss << basic::PosTag::Str(segment->GetTag()) << kSep;
        }
      } else {
        for (size_t i=0; i < segment->GetTags().size(); ++i) {
          multiSs[i] << basic::PosTag::Str(segment->GetTags()[i]) << kSep;
        }
      }
    }

    for (auto &ss : multiSs) {
      patternToMatch = ss.str();
      if (!std::regex_search(patternToMatch.c_str(), wcm, *regex_)) {
        return false;
      }

      const std::wstring &tmpMatched = wcm[0].str();
      if (patternToMatch.substr(0, tmpMatched.length()) != tmpMatched) {
        return false;
      }

      if (matched.empty() || tmpMatched.length() < matched.length()) {
        matched = tmpMatched;
      }
    }
  } else {
    return false;
  }

  Wstrings items;
  StrHelper::SplitStr(matched, kSep, items);
  contentMatched_ = L"";

  size_t i=0;
  for (auto &segment : featureWordposes->GetAll()) {
    if (!items[i].empty()) {
      contentMatched_ += segment->GetQuery(
          context.GetSentence().GetSentence());
    }

    if (++i >= items.size()) {
      break;
    }
  }
  return true;
}

std::wregex* PatternItemWordpos::CreatePattern_(const std::wstring &patternStr) {
  std::wstringstream wss;

  size_t cntSep = 0;
  for (size_t i=0; i < patternStr.length(); ++i) {
    if (kSep == patternStr[i]) {
      ++cntSep;
    }

    if (L'P' == patternStr[i]) {
      wss << L"[a-z0-9]*";
    } else {
      wss << patternStr[i];
    }
  }

  if (0 == cntSep) {
    wss << kSep;
  }
  return new std::wregex(wss.str());
}


}}}
