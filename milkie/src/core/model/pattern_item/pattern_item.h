#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {
    
class Context;    

class PatternItem {
 public: 
  enum Category {
    kPos,
    kDep,
    kInvalid
  };

  bool MatchPattern(Context &context);
  const std::wstring& GetContentMatched() const { return contentMatched_; }
  virtual const std::wstring* AsStr() const;

 public: 
  inline static PatternItem::Category ParseCategory(const std::wstring &category);
  inline static bool IsStartingChar(wchar_t c);
  inline static std::pair<std::shared_ptr<PatternItem>, int> Build(const std::wstring &statement);
  static std::shared_ptr<PatternItem> Build(const StructPatternItem &structPatternItem);
 
 private: 
  std::wstring contentMatched_;
};

typedef std::vector<std::shared_ptr<PatternItem>> PatternItems;

PatternItem::Category PatternItem::ParseCategory(const std::string &category) {
  if ("Pos" == category) {
    return kPos;
  } else if ("Dep" == category) {
    return kDep;
  } else {
    return kInvalid;
  }
}

bool PatternItem::IsStartingChar(wchar_t c) {
  return '"' == c || '#' == c;
}

std::pair<std::shared_ptr<PatternItem>, int> PatternItem::Build(const std::wstring &statement) {
  auto structPatternItem = StructPatternItem::Build(statement);
  return std::make_pair(structPatternItem, structPatternItem.GetStatement().length());
}

}}}
