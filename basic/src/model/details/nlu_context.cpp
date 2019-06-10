#include "../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

NluContext::NluContext(const std::wstring &query) :
    query_(query),
    managerFragmentSet_(new ManagerFragmentSet(query)) {}

NluContext::~NluContext() {
  XFC_DELETE(managerFragmentSet_)
}

void NluContext::Dump(JsonType &jsonType) {
  jsonType["query"] = *(StrHelper::Wstr2Str(query_));
  managerFragmentSet_->Dump(jsonType["fragments"]);
}

std::shared_ptr<NluContext> NluContext::Build(
        const NluContext &nluContext,
        size_t from,
        size_t to) {
  if (from >= to || to >= nluContext.GetQuery().length()) {
    return nullptr;
  }

  std::shared_ptr<NluContext> result = std::make_shared<NluContext>(
          nluContext.GetQuery().substr(from, to));
  XFC_DELETE(result->managerFragmentSet_)
  result->managerFragmentSet_ = nluContext.managerFragmentSet_->Build(from, to);
  return result;
}

}}}
