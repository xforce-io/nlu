#include "../phrase.h"
#include "../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

Phrase::Phrase(
        size_t from,
        size_t len,
        std::shared_ptr<NluContext> nluContext,
        std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag,
        uint32_t strategy) :
    from_(from),
    len_(len),
    nluContext_(std::move(nluContext)),
    collectionSyntaxTag_(std::move(collectionSyntaxTag)),
    strategy_(strategy) {}

void Phrase::GetSubQuery(std::wstring &subQuery) const {
  subQuery = nluContext_->GetQuery().substr(from_, len_);
}

}}}
