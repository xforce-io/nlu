#pragma once

#include "../public.h"
#include "../../struct_element.h"
#include "../pattern_expr.h"

namespace xforce { namespace nlu { namespace milkie {

class Pattern;
class PatternSet;
class PatternExpr;
class CodeSeg;
class StorageKey;
class ReferManager;

class StructPatternExpr :public StructElement {
 public:
  inline StructPatternExpr(
      const std::wstring &statement,
      std::shared_ptr<Pattern> pattern,
      std::shared_ptr<PatternSet> patternSet,
      std::shared_ptr<PatternExpr> patternExpr,
      const PatternExpr::Vector *items,
      std::shared_ptr<CodeSeg> filter,
      const std::wstring *storageSpace,
      const std::wstring *storageKey,
      CategoryPatternExpr::Category categoryPatternExpr);

  inline StructPatternExpr(
      const std::wstring &statement,
      std::shared_ptr<Pattern> &pattern);

  inline StructPatternExpr(
      const std::wstring &statement,
      std::shared_ptr<PatternSet> &patternSet);

  inline StructPatternExpr(
      const std::wstring &statement,
      std::shared_ptr<PatternExpr> &patternExpr);

  virtual ~StructPatternExpr();

  std::shared_ptr<Pattern> GetPattern() const { return pattern_; }
  std::shared_ptr<PatternSet> GetPatternSet() const { return patternSet_; }
  std::shared_ptr<PatternExpr> GetPatternExpr() const { return patternExpr_; }
  const PatternExpr::Vector* GetItems() const { return patternExprs_; }
  std::shared_ptr<CodeSeg> GetFilter() const { return filter_; }
  const StorageKey* GetStorageKey() const { return storageKey_; }
  CategoryPatternExpr::Category GetCategoryPatternExpr() const { return categoryPatternExpr_; }

  static std::shared_ptr<StructPatternExpr> Parse(
          const Conf &conf,
          const ReferManager &referManager,
          const std::wstring &blockKey,
          const std::wstring &statement);

 private:
  std::shared_ptr<Pattern> pattern_;
  std::shared_ptr<PatternSet> patternSet_;
  std::shared_ptr<PatternExpr> patternExpr_;
  PatternExpr::Vector *patternExprs_;
  std::shared_ptr<CodeSeg> filter_;
  StorageKey *storageKey_;
  CategoryPatternExpr::Category categoryPatternExpr_;
};

}}}

#include "../../context/storage_key.h"

namespace xforce { namespace nlu { namespace milkie {

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement,
    std::shared_ptr<Pattern> pattern,
    std::shared_ptr<PatternSet> patternSet,
    std::shared_ptr<PatternExpr> patternExpr,
    const PatternExpr::Vector *items,
    std::shared_ptr<CodeSeg> filter,
    const std::wstring *storageSpace,
    const std::wstring *storageItem,
    CategoryPatternExpr::Category categoryPatternExpr) :
      StructElement(statement),
      pattern_(pattern),
      patternSet_(patternSet),
      patternExpr_(patternExpr),
      patternExprs_(nullptr),
      filter_(filter),
      storageKey_(nullptr),
      categoryPatternExpr_(categoryPatternExpr) {
  if (nullptr != items) {
    patternExprs_ = new PatternExpr::Vector(*items);
  }

  if (nullptr != storageSpace || nullptr != storageItem) {
    storageKey_ = new StorageKey(storageSpace, storageItem);
  }
}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement,
    std::shared_ptr<Pattern> &pattern) :
  StructPatternExpr(
          statement,
          pattern,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          CategoryPatternExpr::kNone) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    std::shared_ptr<PatternSet> &patternSet) :
  StructPatternExpr(
          statement,
          nullptr,
          patternSet,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          CategoryPatternExpr::kNone) {}

StructPatternExpr::StructPatternExpr(
    const std::wstring &statement, 
    std::shared_ptr<PatternExpr> &patternExpr) :
  StructPatternExpr(
          statement,
          nullptr,
          nullptr,
          patternExpr,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          CategoryPatternExpr::kNone) {}

}}}
