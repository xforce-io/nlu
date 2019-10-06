#include "../fragment.h"

namespace xforce { namespace nlu { namespace basic {

Fragment::~Fragment() {
  if (nullptr != str_) {
    XFC_DELETE(str_)
  }
}

bool Fragment::Same(const Fragment &other) const {
  return offset_ == other.offset_ && len_ == other.len_;
}

void Fragment::Dump(JsonType &jsonType) const {
  jsonType["offset"] = offset_;
  jsonType["len"] = len_;
  jsonType["conf"] = confidence_.GetScore();
  jsonType["strategy"] = (size_t)strategy_;
}

}}}
