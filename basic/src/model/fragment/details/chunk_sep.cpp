#include "../chunk_sep.h"

namespace xforce { namespace nlu { namespace basic {

const std::string& ChunkSep::GetCategoryStr() const {
  static const std::string kCategory = "chunkSep";
  return kCategory;
}

void ChunkSep::Dump(JsonType &jsonType) const {
  Super::Dump(jsonType);
  jsonType["type"] = "chunkSep";
}

}}}
