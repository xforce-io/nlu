#include "../chunk_sep.h"

namespace xforce { namespace nlu { namespace basic {

const std::string& ChunkSep::GetCategory() const {
  static const std::string kCategory = "chunkSep";
  return kCategory;
}

}}}
