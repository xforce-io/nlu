#include "../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

NluContext::NluContext(const std::wstring &query) :
    query_(query),
    managerFragmentSet_(new ManagerFragmentSet(query)) {}

NluContext::~NluContext() {
  XFC_DELETE(managerFragmentSet_)
}

std::shared_ptr<NluContext> NluContext::Build(
        size_t from,
        size_t to) {
  if (from >= to || to > GetQuery().length()) {
    return nullptr;
  }

  std::shared_ptr<NluContext> result = std::make_shared<NluContext>(
          GetQuery().substr(from, to-from));
  XFC_DELETE(result->managerFragmentSet_)
  result->managerFragmentSet_ = managerFragmentSet_->Build(from, to);
  return result;
}

std::shared_ptr<NluContext> NluContext::Clone() const {
  auto nluContext = std::make_shared<NluContext>(query_);
  nluContext->managerFragmentSet_ = managerFragmentSet_->Clone();
  return nluContext;
}

void NluContext::Dump(JsonType &jsonType) {
  jsonType["query"] = *(StrHelper::Wstr2Str(query_));
  managerFragmentSet_->Dump(jsonType["fragments"]);
}

}}}
