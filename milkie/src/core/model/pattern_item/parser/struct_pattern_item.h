#pragma once

#include "../public.h"
#include "../../struct_element.h"

namespace xforce { namespace nlu { namespace milkie {

class PatternItem;  

class StructPatternItem : public StructElement {
 public:
  typedef std::vector<std::shared_ptr<StructPatternItem>> Vector;

 public: 
  inline StructPatternItem(
      const std::wstring &statement, 
      const Wstrings &args);

  virtual ~StructPatternItem() {}

  const Wstrings& GetArgs() const { return args_; }
  const std::wstring& GetArgs(size_t i) const { return args_[i]; }

  static std::shared_ptr<StructPatternItem> Parse(const std::wstring &statement);

 private:  
  const Wstrings args_;
};  

StructPatternItem::StructPatternItem(
    const std::wstring &statement, 
    const Wstrings &args) :
  StructElement(statement),
  args_(args) {}

}}}
