#include "../chunk.h"

namespace xforce { namespace nlu { namespace basic {

Chunk::~Chunk() {
  XFC_DELETE(str_)
}

const std::string& Chunk::GetCategory() const {
  static const std::string kCategory = "chunk";
  return kCategory;
}

void Chunk::Dump(JsonType &jsonType) {
  Super::Dump(jsonType);
  jsonType["syn"].Append(*(StrHelper::Wstr2Str(SyntaxTag::Str(syntaxTag_))));
}

}}}
