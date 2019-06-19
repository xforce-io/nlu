#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {
    
class Context;
class StructPatternItem;

class PatternItem {
 public:
  typedef std::vector<std::shared_ptr<PatternItem>> Vector;

 public:
  virtual bool MatchPattern(Context &context) = 0;
  const std::wstring& GetContentMatched() const { return contentMatched_; }
  virtual const std::wstring* AsStr() const;
  virtual ~PatternItem() {}

 public: 
  inline static CategoryPatternItem::Category ParseCategory(const std::wstring &category);
  inline static bool IsStartingChar(wchar_t c);
  inline static std::pair<std::shared_ptr<PatternItem>, ssize_t> Build(const std::wstring &statement);
  static std::shared_ptr<PatternItem> Build(const StructPatternItem &structPatternItem);

 protected:
  std::wstring contentMatched_;
};

}}}

#include "parser/struct_pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

CategoryPatternItem::Category PatternItem::ParseCategory(const std::wstring &category) {
  if (L"Reg" == category) {
    return CategoryPatternItem::kReg;
  } else if (L"Pos" == category) {
    return CategoryPatternItem::kPos;
  } else if (L"Dep" == category) {
    return CategoryPatternItem::kDep;
  } else if (L"Chk" == category) {
    return CategoryPatternItem::kChunk;
  } else {
    return CategoryPatternItem::kInvalid;
  }
}

bool PatternItem::IsStartingChar(wchar_t c) {
  return '"' == c || '#' == c || '%' == c;
}

std::pair<std::shared_ptr<PatternItem>, ssize_t> PatternItem::Build(const std::wstring &statement) {
  auto structPatternItem = StructPatternItem::Parse(statement);
  return std::make_pair(Build(*structPatternItem), structPatternItem->GetStatement().length());
}


}}}
