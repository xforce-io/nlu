#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;
class ForbidItem;

class Rule {
 public:
  static const size_t kCategoryRulePosTag = 1;
  static const size_t kCategoryRuleSyntaxContNp = 2;
  static const size_t kCategoryRuleSyntaxPrep = 3;
  static const size_t kCategoryRuleSyntaxRule = 4;
  static const size_t kCategoryRuleSyntaxVerbArg = 5;
  static const size_t kCategoryRuleSyntaxRpArg = 6;

  static const size_t kMaxLenRepr = 1024;

public:
  Rule();
  Rule(size_t offset, size_t len);

  virtual size_t GetCategory() const = 0;
  virtual const char* GetRepr() const = 0;

  virtual bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) = 0;

  virtual void GenForbid(std::vector<ForbidItem> &forbidItems) const = 0;
  virtual void GenGlobalForbid(std::vector<ForbidItem>&) const {}
  virtual bool GlobalCheckForbid(const ForbidItem&) const { return false; }
  virtual bool PreCheckForbid(const ForbidItem &forbidItem) const = 0;
  virtual bool PostCheckForbid(const ForbidItem &forbidItem) const = 0;

  virtual ~Rule() {}

  virtual Rule* Clone() = 0;

 protected:
  static std::shared_ptr<basic::NluContext> Clone(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext);

 protected:
  mutable char repr_[kMaxLenRepr];
  size_t offset_;
  size_t len_;
};

}}}
