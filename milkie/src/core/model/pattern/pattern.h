#pragma once

#include "public.h"
#include "../pattern_item/pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class Context;  

class Pattern {
 public: 
  inline explicit Pattern(const StructPattern &structPattern);

  bool MatchPattern(Context context);
  const PatternItems& GetPatternItems() const { return patternItems_; }
  inline const std::wstring& GetRepr() const;
  inline const std::wstring* AsStr() const;
  
 private:  
  inline static bool IsStartingChar(wchar_t c); 
  inline static std::pair<std::shared_ptr<Pattern>, size_t> Build(const std::wstring &statement);
  inline static PatternItems CreatePatternItems(const StructPatternItems &structPatternItems);
  inline static std::shared_ptr<Pattern> Build(const StructPattern &structPattern);

 private:
  const StructPattern &structPattern_;
  PatternItems patternItems_;
};

Pattern::Pattern(const StructPattern &structPattern) :
  structPattern_(structPattern) {}

const std::wstring& Pattern::GetRepr() const {
  return structPattern_.GetStatement();
}

const std::wstring* Pattern::AsStr() {
  if (patternItems_.length() == 1) {
    return patternItems_[0]->AsStr();
  }
  return NULL;
}

bool Pattern::IsStartingChar(wchar_t c) {
  return '"' == c || '#' == c;
}

std::pair<std::shared_ptr<Pattern>, size_t> Pattern::Build(const std::wstring &statement) {
  std::shared_ptr<StructPattern> structPattern = StructPattern::Parse(statement);
  return std::make_pair(Build(*structPattern), structPattern->GetStatement().length());
}

PatternItems Pattern::CreatePatternItems(const StructPatternItems &structPatternItems) {
  PatternItems patternItems;
  for (auto &structPatternItem : structPatternItems) {
    auto patternItem = PatternItem::Build(*structPatternItem);
    if (patternItem->get() == NULL) {
      FATAL("illegal_pattern_item(" << structPatternItem->GetStatement() << ")");
    }
    patternItems.push_back(patternItem);
  }
  return patternItems;
}

std::shared_ptr<Pattern> Pattern::Build(const StructPattern &structPattern) {
  return std::make_shared<Pattern>(structPattern);
}

}}}
