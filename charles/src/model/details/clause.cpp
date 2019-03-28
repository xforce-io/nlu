#include "../clause.h"
#include "../base_modules.h"

namespace xforce { namespace nlu { namespace charles {

Clause::Clause(const std::wstring &clause) :
  clause_(clause) {}

Clause::~Clause() {
}

}}}
