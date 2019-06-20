#pragma once

#include "public.h"
#include "pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItemSyntax : public PatternItem {
 public:
  explicit PatternItemSyntax(const basic::SyntaxTag::Type &syntaxType);
  virtual ~PatternItemSyntax() {}

  bool MatchPattern(Context &context) final;

 private:
  basic::SyntaxTag::Type syntaxType_;
};

}}}
