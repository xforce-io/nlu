#pragma once

#include "public.h"
#include "pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItemReg : public PatternItem {
 public:
  explicit PatternItemReg(const std::wstring &patternStr);
  virtual ~PatternItemReg();

  bool MatchPattern(Context &context) final;
  const std::wregex& GetPattern() const { return *regex_; }

 private:
  static std::wregex* CreatePattern_(const std::wstring &patternStr);

 private:
  std::wregex *regex_;
};

}}}
