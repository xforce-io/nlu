#include "../segment.h"

namespace xforce { namespace nlu { namespace basic {

Segment::~Segment() {
  XFC_DELETE(str_)
}

void Segment::Dump(JsonType &jsonType) {
  Super::Dump(jsonType);
  jsonType["pos"] = *(StrHelper::Wstr2Str(PosTag::Str(posTag_)));
}

}}}
