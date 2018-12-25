#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPatternItemCommon : public StructElement {
 public: 
  inline StructPatternItemCommon(
      const std::wstring &statement, 
      const std::vector<std::wstring> &args,
      PatternItem::Category category);

  std::shared_ptr<PatternItem> BuildPattern();

  PatternItem::Category GetCategory() const { return category_; }

  static std::shared_ptr<StructPatternItemCommon> Build(const std::wstring &statement);
 
 private: 
  PatternItem::Category category_;
};

StructPatternItemCommon::StructPatternItemCommon(
    const std::wstring &statement, 
    const std::vector<std::wstring> &args,
    PatternItem::Category category) :
  StructPatternItem(statement, args),
  category_(category) {}

}}}
