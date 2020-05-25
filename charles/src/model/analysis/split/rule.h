#pragma once

#include "../public.h"
#include "../collection_nlu_context.h"

namespace xforce { namespace nlu { namespace charles {

class SplitStage;
class ForbidItem;

class Rule {
 public:
  static const size_t kCategoryRulePosTag = 100;
  static const size_t kCategoryRuleSyntaxContNp = 200;
  static const size_t kCategoryRuleSyntaxPrep = 300;
  static const size_t kCategoryRuleSyntaxRule = 400;
  static const size_t kCategoryRuleSyntaxVerbArg = 500;
  static const size_t kCategoryRuleSyntaxRpArg = 600;
  static const size_t kCategoryRuleSyntaxSplit = 700;

  static const size_t kMaxLenRepr = 1024;

 public:
  Rule();
  Rule(size_t offset, size_t len);

  virtual bool Init() { return true; }
  virtual size_t GetCategory() const = 0;
  virtual const char* GetRepr() const = 0;

  virtual void Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts) = 0;

  virtual void GenForbid(std::vector<ForbidItem>&) const {}
  virtual void GenGlobalForbid(std::vector<ForbidItem>&) const {}
  virtual bool GlobalCheckForbid(const ForbidItem&) const;
  virtual bool PreCheckForbid(const ForbidItem&) const { return false; }
  virtual bool PostCheckForbid(const ForbidItem&) const { return false; }

  size_t GetOffset() const { return offset_; }
  size_t GetLen() const { return len_; }
  size_t GetEnd() const { return offset_+len_; }

  virtual ~Rule() {}

  virtual Rule* Clone() = 0;

 protected:
  static std::shared_ptr<basic::NluContext> Clone(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext);

 protected:
  virtual bool Filter_(const std::shared_ptr<basic::NluContext>&) const { return true; }

 protected:
  mutable char repr_[kMaxLenRepr];
  size_t offset_;
  size_t len_;
};

}}}
