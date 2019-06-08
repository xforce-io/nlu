#pragma once

#include "../../../public.h"
#include "../pattern_expr/pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPatternSet;
class Context;
class Pattern;
class PatternExpr;
class ReferManager;

class PatternSet {
 public: 
  explicit PatternSet(std::shared_ptr<StructPatternSet> structPatternSet);
  virtual ~PatternSet();

  void SetFather(const PatternExpr &patternExpr);

  bool MatchPattern(Context &context);
  void NotifyStorageSpace(const std::wstring &storageSpace);

  const aho_corasick::wtrie* GetPatternStrs() const { return patternStrsTrie_; }
  const PatternExpr::Vector* GetPatternExprs() const { return patternExprs_; }
  const std::wstring& GetRepr() const;

  const std::wstring* AsStr() const;

  inline static bool IsStartingChar(wchar_t c);
  static std::pair<std::shared_ptr<PatternSet>, ssize_t > Build(
          const ReferManager &referManager,
          const std::wstring &blockKey,
          const std::wstring &statement);
  static std::shared_ptr<PatternSet> Build(
          const StructPatternSet &structPatternSet);

 private:
  inline aho_corasick::wtrie* BuildPatternStrsTrie_(
      const std::unordered_set<std::wstring> *patternStrs);

 private:
  const PatternExpr *father_;

  std::shared_ptr<StructPatternSet> structPatternSet_;
  size_t maxLengthPatternStrs_; 
  aho_corasick::wtrie *patternStrsTrie_;
  const PatternExpr::Vector *patternExprs_;
};

bool PatternSet::IsStartingChar(wchar_t c) {
  return L'[' == c;
}

aho_corasick::wtrie* PatternSet::BuildPatternStrsTrie_(
    const std::unordered_set<std::wstring> *patternStrs) {
  if (nullptr == patternStrs) {
    return nullptr;
  }

  aho_corasick::wtrie *patternStrsTrie = new aho_corasick::wtrie();
  for (auto patternStr : *patternStrs) {
    if (!patternStr.empty()) {
      patternStrsTrie->insert(patternStr);
      if (patternStr.length() > maxLengthPatternStrs_) {
        maxLengthPatternStrs_ = patternStr.length();
      }
    }
  }
  return patternStrsTrie;
}

}}}
