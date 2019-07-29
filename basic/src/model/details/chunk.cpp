#include "../chunk.h"

namespace xforce { namespace nlu { namespace basic {

const std::string& Chunk::GetCategory() const {
  static const std::string kCategory = "chunk";
  return kCategory;
}

void Chunk::Dump(JsonType &jsonType) {
  Super::Dump(jsonType);
  for (auto &syntaxTag : tags_) {
    jsonType["syn"].Append(*(StrHelper::Wstr2Str(SyntaxTag::Str(syntaxTag))));
  }
}

}}}
