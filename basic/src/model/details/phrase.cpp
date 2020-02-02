#include "../phrase.h"
#include "../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

Phrase::Phrase(
        size_t from,
        size_t to,
        std::shared_ptr<NluContext> nluContext,
        std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag,
        std::string strategy) :
    from_(from),
    to_(to),
    nluContext_(std::move(nluContext)),
    collectionSyntaxTag_(std::move(collectionSyntaxTag)),
    strategy_(std::move(strategy)) {}

}}}
