#pragma once

#include "public.h"
#include "../pattern_item/pattern_item.h"
#include "../pattern_item/parser/struct_pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPattern;
class Context;

class Pattern {
 public:
  inline explicit Pattern(const StructPattern &structPattern);

  bool MatchPattern(Context &context);
  const PatternItem::Vector & GetPatternItems() const { return patternItems_; }
  inline const std::wstring& GetRepr() const;
  inline const std::wstring* AsStr() const;

  inline static bool IsStartingChar(wchar_t c);
  inline static std::pair<std::shared_ptr<Pattern>, size_t> Build(const std::wstring &statement);

 private:
  inline static PatternItem::Vector CreatePatternItems(const StructPatternItem::Vector &structPatternItems);
  inline static std::shared_ptr<Pattern> Build(const StructPattern &structPattern);

 private:
  const StructPattern &structPattern_;
  PatternItem::Vector patternItems_;
};

}}}

#include "../pattern/parser/struct_pattern.h"
#include "../pattern_item/parser/struct_pattern_item.h"

namespace xforce { namespace nlu { namespace milkie {

Pattern::Pattern(const StructPattern &structPattern) :
    structPattern_(structPattern) {
  patternItems_ = CreatePatternItems(structPattern.GetPatternItems());
}

const std::wstring& Pattern::GetRepr() const {
  return structPattern_.GetStatement();
}

const std::wstring* Pattern::AsStr() const {
  if (patternItems_.size() == 1) {
    return patternItems_[0]->AsStr();
  }
  return nullptr;
}

bool Pattern::IsStartingChar(wchar_t c) {
  return '"' == c || '#' == c;
}

std::pair<std::shared_ptr<Pattern>, size_t> Pattern::Build(const std::wstring &statement) {
  std::shared_ptr<StructPattern> structPattern = StructPattern::Parse(statement);
  return std::make_pair(Build(*structPattern), structPattern->GetStatement().length());
}

PatternItem::Vector Pattern::CreatePatternItems(const StructPatternItem::Vector &structPatternItems) {
  PatternItem::Vector patternItems;
  for (auto &structPatternItem : structPatternItems) {
    auto patternItem = PatternItem::Build(*structPatternItem);
    if (patternItem.get() == nullptr) {
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
