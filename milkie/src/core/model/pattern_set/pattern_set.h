#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternSet {
 public: 
  explicit PatternSet(const StructPatternSet &structPatternSet); 

 private:
  static aho_corasick::wtrie* BuildPatternStrsTrie_(
      const std::unordered_set<std::wstring> *patternStrs);

 private:
  const StructPatternSet *structPatternSet_;
  size_t maxLengthPatternStrs_; 
  aho_corasick::wtrie *patternStrsTrie_;
};

aho_corasick::wtrie* PatternSet::BuildPatternStrsTrie_(
    const std::unordered_set<std::wstring> *patternStrs) {
  if (NULL == patternStrs) {
    return NULL;
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

}}}
