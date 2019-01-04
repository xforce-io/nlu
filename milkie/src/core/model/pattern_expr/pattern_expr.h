#pragma once

#include "public.h"
#include "../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

class Pattern;
class PatternSet;
class StructPatternExpr;

class PatternExpr {
 public:
  PatternExpr(
      std::shared_ptr<Pattern> pattern,
      std::shared_ptr<PatternSet> patternSet,
      const std::wstring *wildcardName,
      std::shared_ptr<StructPatternExpr> structPatternExpr);

  virtual ~PatternExpr();

  inline explicit PatternExpr(std::shared_ptr<Pattern> pattern);
  inline explicit PatternExpr(std::shared_ptr<PatternSet> patternSet);
  inline explicit PatternExpr(const std::wstring &wildcardName);
  inline explicit PatternExpr(const StructPatternExpr &structPatternExpr);

  CategoryPatternExpr::Category GetRepeatPattern() const { return repeatPattern_; }
  std::wstring GetRepr() const;
  inline void SetStorageKey(const std::wstring &storageStored);
  inline bool ExactMatch(Context &context);
  inline bool ExactMatch(Context &context, bool singleton);
  bool MatchPattern(Context &context, bool singleton);
  ssize_t MatchFromIdx(ssize_t fromIdx, Context &context);
  bool MatchForWildcard(Context &context, ssize_t itemIdx);
  void StopMatch(bool succ, Context &context, bool singleton);
  const std::wstring* AsWildcard() const { return wildcardName_; }
  const std::wstring* AsStr() const;

 private:
  void DebugMatch_(Context &context, ssize_t startIdx, bool ok);

  static std::unordered_set<char> CreateInvalidLeadPosForWildcard();
  static std::unordered_set<std::string> CreateInvalidFullPosForWildcard();

 private: 
  std::shared_ptr<Pattern> pattern_;
  std::shared_ptr<PatternSet> patternSet_;
  const std::wstring *wildcardName_;
  std::shared_ptr<StructPatternExpr> structPatternExpr_;

  std::vector<std::shared_ptr<PatternExpr>> items_;
  const std::wstring *storage_;
  CategoryPatternExpr::Category repeatPattern_;

  static std::unordered_set<char> invalidLeadPosForWildcard_;
  static std::unordered_set<std::string> invalidFullPosForWildcard_;
};

typedef std::vector<std::shared_ptr<PatternExpr>> PatternExprs;

PatternExpr::PatternExpr(std::shared_ptr<Pattern> &pattern) :
  PatternExpr(pattern, nullptr, nullptr, nullptr) {}

PatternExpr::PatternExpr(std::shared_ptr<PatternSet> &patternSet) :
  PatternExpr(nullptr, &patternSet, nullptr, nullptr) {}

PatternExpr::PatternExpr(const std::wstring &wildcardName) :
  PatternExpr(nullptr, nullptr, &wildcardName, nullptr) {}

PatternExpr::PatternExpr(const StructPatternExpr &structPatternExpr) :
  PatternExpr(nullptr, nullptr, nullptr, &structPatternExpr) {}

void PatternExpr::SetStorageKey(const std::wstring &storageStored) {
    if (nullptr == storage_) {
        storage_ = &storageStored;
    }
}

bool PatternExpr::ExactMatch(Context &context) {
  return MatchPattern(context, false) && context.End();
}

bool PatternExpr::ExactMatch(Context &context, bool singleton) {
  return MatchPattern(context, singleton) && context.End();
}

}}}
