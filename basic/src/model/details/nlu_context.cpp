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

std::shared_ptr<NluContext> NluContext::Clone() {
  auto nluContext = std::make_shared<NluContext>(query_);
  nluContext->managerFragmentSet_ = managerFragmentSet_->Clone();
  return nluContext;
}

Stage::Val NluContext::Split(std::vector<std::shared_ptr<NluContext>> &nluContexts) {
  auto iterSeg = GetSegments().GetAll().begin();
  size_t idx=0;
  while (iterSeg != GetSegments().GetAll().end()) {
    if ((*iterSeg)->GetTags().size() > 1) {
      for (auto tag : ((*iterSeg)->GetTags())) {
        auto newNluContext = Clone();
        newNluContext->AdjustSegTags_(idx, tag);
        nluContexts.push_back(newNluContext);
      }
      return Stage::kSegment;
    }
    ++iterSeg;
    ++idx;
  }
  return Stage::kNone;
}

void NluContext::Dump(JsonType &jsonType) {
  jsonType["query"] = *(StrHelper::Wstr2Str(query_));
  managerFragmentSet_->Dump(jsonType["fragments"]);
}

void NluContext::AdjustSegTags_(size_t i, PosTag::Type::Val posTag) {
  auto iterSeg = GetSegments().GetAll().begin();
  size_t idx=0;
  while (iterSeg != GetSegments().GetAll().end()) {
    if (idx == i) {
      (*iterSeg)->SetTag(posTag);
      break;
    }
    ++iterSeg;
    ++idx;
  }
}

}}}
