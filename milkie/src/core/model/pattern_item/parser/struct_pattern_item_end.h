#pragma once

#include "../public.h"
#include "struct_pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPatternItemEnd : public StructPatternItem {
 public:
  StructPatternItemEnd(
      const std::wstring &statement,
      const std::vector<std::wstring> &args);

  static std::shared_ptr<StructPatternItemEnd> Build(const std::wstring &statement);
};

}}}
