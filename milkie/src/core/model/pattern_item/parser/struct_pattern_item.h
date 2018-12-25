#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItem;  

class StructPatternItem : public StructElement {
 public: 
  inline StructPatternItem(
      const std::wstring &statement, 
      const Wstrings &args);

  virtual ~StructPatternItem() {}

  virtual std::shared_ptr<PatternItem> BuildPattern() = 0;

  const Wstrings& GetArgs() const { return args_; }
  const std::wstring& GetArgs(size_t i) const { return args_[i]; }

  static std::shared_ptr<StructPatternItem> Build(const std::wstring &statement);

 private:  
  const Wstrings args_;
};  

typedef std::vector<std::shared_ptr<StructPatternItem>> StructPatternItems;

StructPatternItem::StructPatternItem(
    const std::wstring &statement, 
    const Wstrings &args) :
  StructElement(statement),
  args_(args) {}

}}}
