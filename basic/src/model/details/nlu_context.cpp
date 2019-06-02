#include "../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

NluContext::NluContext(const std::wstring &query) :
    query_(query),
    managerFragmentSet_(query) {}

void NluContext::Dump(JsonType &jsonType) {
  jsonType["query"] = query_;
  managerFragmentSet_.Dump(jsonType["fragments"]);
}

}}}
