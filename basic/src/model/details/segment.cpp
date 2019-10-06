#include "../segment.h"

namespace xforce { namespace nlu { namespace basic {

const std::string& Segment::GetCategory() const {
  static const std::string kCategory = "segment";
  return kCategory;
}

void Segment::Dump(JsonType &jsonType) const {
  Super::Dump(jsonType);
  jsonType["type"] = "segment";
  for (auto &posTag : tags_) {
    jsonType["pos"].Append(*(StrHelper::Wstr2Str(PosTag::Str(posTag))));
  }
}

}}}
