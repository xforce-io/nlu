#include "../pattern_item_end.h"
#include "../../context/context.h"

namespace xforce { namespace nlu { namespace milkie {

bool PatternItemEnd::MatchPattern(Context &context) {
  return context.End();
}


}}}
