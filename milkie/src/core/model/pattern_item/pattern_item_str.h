#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Context;  

class PatternItemStr : public PatternItem {
 public: 
  explicit PatternItemStr(const std::wstring &patternStr);

  bool MatchPattern(const Context &context);
  const std::wstring& GetPatternStr() const { return patternStr_; } 

 private:
  std::wstring patternStr_;
};  

}}}
