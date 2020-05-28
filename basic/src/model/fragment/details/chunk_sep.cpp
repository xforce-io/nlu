#include "../chunk_sep.h"

namespace xforce { namespace nlu { namespace basic {

void ChunkSep::Dump(JsonType &jsonType) const {
  Super::Dump(jsonType);
  jsonType["type"] = "chunkSep";
}

}}}
