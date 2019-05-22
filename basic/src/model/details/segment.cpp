#include "../segment.h"

namespace xforce { namespace nlu { namespace basic {

void Segment::Dump(JsonType &jsonType) {
  Super::Dump(jsonType);
  for (auto &posTag : posTags_) {
    jsonType["pos"].Append(*(StrHelper::Wstr2Str(PosTag::Str(posTag))));
  }
}

}}}
