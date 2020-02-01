#include "../phrase.h"
#include "../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

Phrase::Phrase(
        size_t from,
        size_t to,
        std::shared_ptr<NluContext> nluContext,
        CollectionSyntaxTag collectionSyntaxTag) :
    from_(from),
    to_(to),
    nluContext_(nluContext),
    collectionSyntaxTag_(collectionSyntaxTag) {}

}}}
