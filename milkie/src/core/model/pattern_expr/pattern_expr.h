#pragma once

#include "public.h"
#include "../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

class Pattern;
class PatternSet;
class StructPatternExpr;
class CodeSeg;
class StorageKey;
class ReferManager;

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
  inline bool ExactMatch(Context &context) const;
  inline bool ExactMatch(Context &context, bool singleton) const;
  inline bool PartlyMatch(Context &context) const;
  inline bool PartlyMatch(Context &context, bool singleton) const;
  inline bool PrefixMatch(Context &context, bool singleton) const;
  ssize_t MatchFromIdx(ssize_t fromIdx, Context &context) const;
  bool MatchForWildcard(Context &context, ssize_t itemIdx) const;
  void StopMatch(bool succ, Context &context, bool singleton) const;
  const std::wstring* AsWildcard() const { return wildcardName_; }
  const std::wstring* AsStr() const;

  static bool IsExactStartingChar(char c);
  static bool IsPatternExprStartingChar(char c);
  static bool IsPatternExprExactStartingChar(char c);
  static bool IsPatternExprPrefixStartingChar(char c);
  static bool IsPatternExprPartlyStartingChar(char c);
  static std::pair<std::shared_ptr<PatternExpr>, ssize_t> Build(
          const ReferManager &referManager,
          const std::wstring &blockKey,
          const std::wstring &statement);
  static std::shared_ptr<PatternExpr> Build(std::shared_ptr<Pattern> &pattern);
  static std::shared_ptr<PatternExpr> Build(std::shared_ptr<PatternSet> &patternSet);

 private:
  bool MatchPattern_(Context &context, bool singleton) const;
  void DebugMatch_(Context &context, ssize_t startIdx, bool ok) const;

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

bool PatternExpr::ExactMatch(Context &context) const {
  return ExactMatch(context, false);
}

bool PatternExpr::ExactMatch(Context &context, bool singleton) const {
  bool ret = MatchPattern_(context, singleton) && context.End();
  if (ret) {
    context.Store();
  }
  return ret;
}

bool PatternExpr::PartlyMatch(Context &context) const {
  return PartlyMatch(context, false);
}

bool PatternExpr::PartlyMatch(Context &context, bool singleton) const {
  bool ret = false;
  size_t curPos = 0;
  Context *tmpContext = nullptr;
  while (curPos < context.GetSentence().GetSentence().length()) {
    if (nullptr==tmpContext) {
      tmpContext = &context;
      tmpContext->Reset();
      tmpContext->SetStartPos(curPos);
    } else {
      tmpContext = new Context(context.GetSentence().GetSentence());
    }

    tmpContext->SetCurPos(curPos);
    if (MatchPattern_(context, singleton)) {
      curPos = tmpContext->GetCurPos();
      tmpContext->Store();
      ret = true;

      if (tmpContext != &context) {
        context.GetStorage().Merge(tmpContext->GetStorage());
      }
    } else {
      ++curPos;
    }

    if (tmpContext != &context) {
      XFC_DELETE(tmpContext)
    }
  }
  return ret;
}

/*

   bool ret = false;
  size_t curPos = 0;
  while (curPos < context.GetSentence().GetSentence().length()) {
    context.Reset();
    context.SetStartPos(curPos);
    context.SetCurPos(curPos);
    if (MatchPattern_(context, singleton)) {
      curPos = context.GetCurPos();
      context.Store();
      ret = true;
    } else {
      ++curPos;
    }
  }
  return ret;

 */

bool PatternExpr::PrefixMatch(Context &context, bool singleton) const {
  bool ret = MatchPattern_(context, singleton);
  if (ret) {
    context.Store();
  }
  return ret;
}

}}}
