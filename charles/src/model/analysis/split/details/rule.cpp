#include "../rule.h"
#include "../split_stage.h"

namespace xforce { namespace nlu { namespace charles {

std::shared_ptr<basic::NluContext> Rule::Clone(
        const SplitStage &splitStage,
        const std::shared_ptr<basic::NluContext> &nluContext) {
  auto newNluContext = nluContext->Clone();
  newNluContext->Reset(splitStage.GetCurStage());
  return newNluContext;
}

}}}
