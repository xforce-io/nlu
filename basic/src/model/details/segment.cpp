#include "../segment.h"

namespace xforce { namespace nlu { namespace basic {

Segment::~Segment() {
  XFC_DELETE(str_)
}

void Segment::Dump(JsonType &jsonType) {
  jsonType["pos"] = *(StrHelper::Wstr2Str(PosTag::Str(posTag_)));
  jsonType["offset"] = offset_;
  jsonType["len"] = len_;
}

}}}
