#pragma once

#include "public.h"
#include "pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItemEnd : public PatternItem {
 public:
  explicit PatternItemEnd() {}
  virtual ~PatternItemEnd() {}

  bool MatchPattern(Context &context) final;
};

}}}
