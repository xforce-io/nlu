#include "../person_name.h"

namespace xforce { namespace nlu { namespace ner {

PersonName::PersonName(
    const std::wstring &name, 
    size_t offset) :
  NameEntity(offset, name.length()),
  name_(name) {}

}}}
