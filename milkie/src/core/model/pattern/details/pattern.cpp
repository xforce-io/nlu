#include "../pattern.h"
#include "../../context/context.h"
#include "../../pattern_item/pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

bool Pattern::MatchPattern(Context &context) {
  const std::wstring *contentMatched = nullptr;
  for (auto &patternItem : patternItems_) {
    if (!patternItem->MatchPattern(context)) {
      return false;
    }

    if (nullptr == contentMatched) {
      contentMatched = &(patternItem->GetContentMatched());
    } else if (!(*contentMatched == patternItem->GetContentMatched())) {
      return false;
    }
  }
  context.Pass(patternItems_.front()->GetContentMatched().length());
}

}}}