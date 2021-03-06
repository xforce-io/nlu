#include "../nlu_context.h"
#include "../phrase.h"

namespace xforce { namespace nlu { namespace basic {

NluContext::NluContext(const std::wstring &query) :
    query_(query),
    isValid_(true),
    managerFragmentSet_(new ManagerFragmentSet(query)) {}

NluContext::~NluContext() {
  XFC_DELETE(managerFragmentSet_)
}

void NluContext::AddPhrase(
        size_t from,
        size_t len,
        std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag,
        uint32_t strategy) {
  phrases_.push_back(Phrase(
          from,
          len,
          *this,
          std::move(collectionSyntaxTag),
          strategy));
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
  nluContext->isValid_ = isValid_;
  nluContext->managerFragmentSet_ = managerFragmentSet_->Clone();
  nluContext->phrases_ = phrases_;
  for (auto &phrase : nluContext->phrases_) {
    phrase.SetNluContext(*nluContext);
  }
  return nluContext;
}

void NluContext::Reset(basic::Stage::Val stage) {
  switch (stage) {
    case basic::Stage::kNone :
      GetSegments().Clear();
      GetNameEntities().Clear();
      GetChunkSeps().Clear();
      GetChunks().Clear();
      return;
    case basic::Stage::kSegment :
      GetChunkSeps().Clear();
      GetChunks().Clear();
      return;
    case basic::Stage::kPosTag :
      GetChunkSeps().Clear();
      GetChunks().Clear();
      return;
    case basic::Stage::kChunk :
      GetChunks().Clear();
      return;
    case basic::Stage::kSyntax :
      return;
    default:
      return;
  }
}

void NluContext::Dump(JsonType &jsonType, const NluContext *diff) const {
  jsonType["query"] = query_;
  jsonType["isValid"] = isValid_;
  managerFragmentSet_->Dump(
          jsonType["fragments"],
          nullptr != diff ? diff->managerFragmentSet_ : nullptr);

  size_t i=0;
  for (auto &phrase : phrases_) {
    jsonType["phrase"][i]["query"] = query_.substr(
            phrase.GetFrom(),
            phrase.GetLen());
    ++i;
  }
}

void NluContext::Dump(std::string &json) const {
  xforce::JsonType jsonToDump;
  Dump(jsonToDump);

  std::stringstream ss;
  jsonToDump.DumpJson(ss);
  json = ss.str();
}

}}}
