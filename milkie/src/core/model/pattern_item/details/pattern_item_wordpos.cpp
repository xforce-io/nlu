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
    if (segment->GetPosTags().size() > 1) {
      ++numMulti;
      sizeMulti = segment->GetPosTags().size();
    }
  }

  std::wcmatch wcm;
  std::wstring patternToMatch;
  if (0 == numMulti) {
    std::wstringstream ss;
    for (auto &segment : featureWordposes->GetAll()) {
      ss << basic::PosTag::Str(segment->GetPosTag()) << kSep;
    }

    patternToMatch = ss.str();
    if (!std::regex_search(patternToMatch.c_str(), wcm, *regex_)) {
      return false;
    }
  } else if (numMulti<=1) {
    std::vector<std::wstringstream> multiSs;
    multiSs.resize(sizeMulti);
    for (auto &segment : featureWordposes->GetAll()) {
      if (segment->GetPosTags().size() == 1) {
        for (auto &ss : multiSs) {
          ss << basic::PosTag::Str(segment->GetPosTag()) << kSep;
        }
      } else {
        for (size_t i=0; i < segment->GetPosTags().size(); ++i) {
          multiSs[i] << basic::PosTag::Str(segment->GetPosTags()[i]) << kSep;
        }
      }
    }

    for (auto &ss : multiSs) {
      patternToMatch = ss.str();
      if (!std::regex_search(patternToMatch.c_str(), wcm, *regex_)) {
        return false;
      }
    }
  } else {
    return false;
  }

  const std::wstring &matched = wcm[0].str();
  if (patternToMatch.substr(0, matched.length()) == matched) {
    Wstrings items;
    StrHelper::SplitStr(matched, kSep, items);
    contentMatched_ = L"";
    for (size_t i=0; i < items.size(); ++i) {
      if (!items[i].empty()) {
        contentMatched_ += (*featureWordposes)[i]->GetQuery(
            context.GetSentence().GetSentence());
      }
    }
    return true;
  }
  return false;
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
