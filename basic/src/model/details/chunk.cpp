#include "../chunk.h"

namespace xforce { namespace nlu { namespace basic {

Chunk::~Chunk() {
  XFC_DELETE(str_)
}

void Chunk::Dump(JsonType &jsonType) {
  Super::Dump(jsonType);
  jsonType["syn"].Append(*(StrHelper::Wstr2Str(SyntaxTag::Str(syntaxTag_))));
}

}}}
