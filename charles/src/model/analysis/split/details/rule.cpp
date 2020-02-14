#include "../rule.h"
#include "../split_stage.h"
#include "../forbid_item.h"

namespace xforce { namespace nlu { namespace charles {

Rule::Rule() :
    offset_(0),
    len_(0) {}

Rule::Rule(size_t offset, size_t len) :
    offset_(offset),
    len_(len) {}

bool Rule::GlobalCheckForbid(const ForbidItem &forbidItem) const {
  if (0 == len_) {
    return false;
  }

  if (forbidItem.GetCategoryRule() == ForbidItem::kCategoryGlobalRuleInterval) {
    return forbidItem.Overlap(offset_, len_);
  }
  return false;
}

std::shared_ptr<basic::NluContext> Rule::Clone(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext) {
  auto newNluContext = nluContext->Clone();
  newNluContext->Reset(splitStage.GetCurStage());
  return newNluContext;
}

}}}
