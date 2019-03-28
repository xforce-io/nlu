#pragma once

#include "public.h"
#include "pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItemSyntax : public PatternItem {
 public:
  explicit PatternItemSyntax(const std::wstring &pattern);
  virtual ~PatternItemSyntax() {}

  bool MatchPattern(Context &context) final;

 private:
  std::wstring pattern_;
};

}}}
