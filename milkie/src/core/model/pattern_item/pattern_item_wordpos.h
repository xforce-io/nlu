#pragma once

#include "public.h"
#include "pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItemWordpos : public PatternItem {
 private:
  static const wchar_t kSep; 

 public: 
  PatternItemWordpos(const std::wstring &patternStr);
  virtual ~PatternItemWordpos();

  bool MatchPattern(const Context &context);
  const std::wregex& GetPattern() const { return *regex_; }

 private: 
  static std::wregex CreatePattern_(const std::wstring &patternStr);

 private:
  std::wregex *regex_;
};

}}}
