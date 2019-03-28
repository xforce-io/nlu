#pragma once

#include "../public.h"
#include "struct_pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPatternItemStr : public StructPatternItem {
 public:
  inline StructPatternItemStr(
      const std::wstring &statement,
      const std::vector<std::wstring> &args,
      const std::wstring &patternStr);

  static std::shared_ptr<StructPatternItemStr> Build(const std::wstring &statement);

  const std::wstring& GetPatternStr() const { return patternStr_; }

 private:
  std::wstring patternStr_;
};

StructPatternItemStr::StructPatternItemStr(
      const std::wstring &statement,
      const std::vector<std::wstring> &args,
      const std::wstring &patternStr) :
  StructPatternItem(statement, args),
  patternStr_(patternStr) {}

}}}