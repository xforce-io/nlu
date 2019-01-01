#pragma once

#include "public.h"
#include "parser/struct_pattern_set.h"

namespace xforce { namespace nlu { namespace milkie {

class Context;
class Pattern;
class PatternExprs;

class PatternSet {
 public: 
  explicit PatternSet(const StructPatternSet &structPatternSet); 

  bool MatchPattern(Context &context);

  const aho_corasick::wtrie& GetPatternStrs() const { return *patternStrsTrie_; }
  const PatternExprs& GetPatternExprs() const { return patternExprs_; }
  const std::wstring& GetRepr() const { return structPatternSet_->GetStatement(); }

  const std::string& AsStr() const;

  static bool IsStartingChar(wchar_t c);
  static std::pair<std::shared_ptr<PatternSet>, int> Build(const std::wstring &blockKey, const std::wstring &statement);
  static std::shared_ptr<Pattern> Build(const StructPatternSet &structPatternSet);

 private:
  aho_corasick::wtrie* BuildPatternStrsTrie_(
      const std::unordered_set<std::wstring> *patternStrs);

 private:
  const StructPatternSet *structPatternSet_;
  size_t maxLengthPatternStrs_; 
  aho_corasick::wtrie *patternStrsTrie_;
  const PatternExprs &patternExprs_;
};

aho_corasick::wtrie* PatternSet::BuildPatternStrsTrie_(
    const std::unordered_set<std::wstring> *patternStrs) {
  if (nullptr == patternStrs) {
    return nullptr;
  }

  aho_corasick::wtrie *patternStrsTrie = new aho_corasick::wtrie();
  for (auto patternStr : *patternStrs) {
    if (!patternStr.empty()) {
      patternStrsTrie_->insert(patternStr);
      if (patternStr.length() > maxLengthPatternStrs_) {
        maxLengthPatternStrs_ = patternStr.length();
      }
    }
  }
  return patternStrsTrie;
}

bool PatternSet::IsStartingChar(wchar_t c) {
  return L'[' == c;
}

}}}
