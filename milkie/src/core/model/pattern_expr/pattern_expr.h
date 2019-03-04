#pragma once

#include "public.h"
#include "../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

class Pattern;
class PatternSet;
class StructPatternExpr;
class CodeSeg;
class StorageKey;

class PatternExpr {
 public:
  typedef std::vector<std::shared_ptr<PatternExpr>> Vector;

 public:
  PatternExpr(
      std::shared_ptr<Pattern> pattern,
      std::shared_ptr<PatternSet> patternSet,
      const std::wstring *wildcardName,
      std::shared_ptr<StructPatternExpr> structPatternExpr);

  virtual ~PatternExpr();

  inline explicit PatternExpr(std::shared_ptr<Pattern> &pattern);
  inline explicit PatternExpr(std::shared_ptr<PatternSet> &patternSet);
  inline explicit PatternExpr(const std::wstring &wildcardName);
  inline explicit PatternExpr(std::shared_ptr<StructPatternExpr> &structPatternExpr);

  void SetFather(const PatternExpr &patternExpr);
  CategoryPatternExpr::Category GetRepeatPattern() const { return repeatPattern_; }
  std::wstring GetRepr() const;
  inline void SetStorageKey(const std::wstring &item);
  inline void SetStorageKey(const StorageKey &storageKey);
  void NotifyStorageSpace(const std::wstring &storageSpace);
  inline bool ExactMatch(Context &context);
  inline bool ExactMatch(Context &context, bool singleton);
  inline bool PartlyMatch(Context &context);
  inline bool PartlyMatch(Context &context, bool singleton);
  bool MatchPattern(Context &context, bool singleton);
  ssize_t MatchFromIdx(ssize_t fromIdx, Context &context);
  bool MatchForWildcard(Context &context, ssize_t itemIdx);
  void StopMatch(bool succ, Context &context, bool singleton);
  const std::wstring* AsWildcard() const { return wildcardName_; }
  const std::wstring* AsStr() const;

  static bool IsExactStartingChar(char c);
  static bool IsPatternExprStartingChar(char c);
  static bool IsPatternExprExactStartingChar(char c);
  static bool IsPatternExprPrefixStartingChar(char c);
  static bool IsPatternExprPartlyStartingChar(char c);
  static std::pair<std::shared_ptr<PatternExpr>, ssize_t> Build(
          const std::wstring &blockKey,
          const std::wstring &statement);
  static std::shared_ptr<PatternExpr> Build(std::shared_ptr<Pattern> &pattern);
  static std::shared_ptr<PatternExpr> Build(std::shared_ptr<PatternSet> &patternSet);

 private:
  void DebugMatch_(Context &context, ssize_t startIdx, bool ok);

  static std::unordered_set<wchar_t> CreateInvalidLeadPosForWildcard();
  static std::unordered_set<std::wstring> CreateInvalidFullPosForWildcard();

 private:
  const PatternExpr *father_;

  std::shared_ptr<Pattern> pattern_;
  std::shared_ptr<PatternSet> patternSet_;
  const std::wstring *wildcardName_;
  std::shared_ptr<StructPatternExpr> structPatternExpr_;

  std::vector<std::shared_ptr<PatternExpr>> items_;
  std::shared_ptr<CodeSeg> filter_;
  StorageKey *storageKey_;
  CategoryPatternExpr::Category repeatPattern_;

  static std::unordered_set<wchar_t> invalidLeadPosForWildcard_;
  static std::unordered_set<std::wstring> invalidFullPosForWildcard_;
};

PatternExpr::PatternExpr(std::shared_ptr<Pattern> &pattern) :
  PatternExpr(pattern, nullptr, nullptr, nullptr) {}

PatternExpr::PatternExpr(std::shared_ptr<PatternSet> &patternSet) :
  PatternExpr(nullptr, patternSet, nullptr, nullptr) {}

PatternExpr::PatternExpr(const std::wstring &wildcardName) :
  PatternExpr(nullptr, nullptr, &wildcardName, nullptr) {}

PatternExpr::PatternExpr(std::shared_ptr<StructPatternExpr> &structPatternExpr) :
  PatternExpr(nullptr, nullptr, nullptr, structPatternExpr) {}

void PatternExpr::SetStorageKey(const std::wstring &item) {
  if (nullptr == storageKey_) {
    storageKey_ = new StorageKey();
  }
  storageKey_->SetSpace(nullptr);
  storageKey_->SetItem(&item);
}

void PatternExpr::SetStorageKey(const StorageKey &storageKey) {
  if (nullptr == storageKey_) {
    storageKey_ = new StorageKey();
  }
  *storageKey_ = storageKey;
}

bool PatternExpr::ExactMatch(Context &context) {
  return ExactMatch(context, false);
}

bool PatternExpr::ExactMatch(Context &context, bool singleton) {
  return MatchPattern(context, singleton) && context.End();
}

bool PatternExpr::PartlyMatch(Context &context) {
  return PartlyMatch(context, false);
}

bool PatternExpr::PartlyMatch(Context &context, bool singleton) {
  for (size_t curPos=0; curPos < context.GetSentence().GetSentence().length(); ++curPos) {
    context.Reset();
    context.SetCurPos(curPos);
    if (MatchPattern(context, singleton)) {
      return true;
    }
  }
  return false;
}

}}}
