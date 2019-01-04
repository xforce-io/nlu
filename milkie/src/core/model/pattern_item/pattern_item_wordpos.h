#pragma once

#include "public.h"
#include "pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItemWordpos : public PatternItem {
 private:
  static const wchar_t kSep; 

 public: 
  explicit PatternItemWordpos(const std::wstring &patternStr);
  virtual ~PatternItemWordpos();

  bool MatchPattern(Context &context) final;
  const std::wregex& GetPattern() const { return *regex_; }

 private: 
  static std::wregex* CreatePattern_(const std::wstring &patternStr);

 private:
  std::wregex *regex_;
};

}}}
