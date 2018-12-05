#include "../person_name.h"

namespace xforce { namespace nlu { namespace ner {

PersonName::WcharSet PersonName::forbiddenChars_ = CreateForbiddenChars_(); 

PersonName::PersonName(
    const std::wstring &name, 
    size_t offset) :
  NameEntity(offset, name.length()),
  name_(name) {}

PersonName::WcharSet PersonName::CreateForbiddenChars_() {
  WcharSet wcharSet;
  wcharSet.insert(L'的');
  return wcharSet;
}

}}}
