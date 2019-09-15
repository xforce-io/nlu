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

public:
  virtual size_t GetCategory() const = 0;

  virtual bool Split(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) = 0;

  virtual bool GenForbid(ForbidItem &forbidItem) const = 0;
  virtual bool PreCheckForbid(const ForbidItem &forbidItem) const = 0;
  virtual bool PostCheckForbid(const ForbidItem &forbidItem) const = 0;

  virtual ~Rule() {}

  virtual Rule* Clone() = 0;

 protected:
  static std::shared_ptr<basic::NluContext> Clone(
          const SplitStage &splitStage,
          const std::shared_ptr<basic::NluContext> &nluContext);
};

}}}
