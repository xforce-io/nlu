#include "../fragment.h"

namespace xforce { namespace nlu { namespace basic {

Fragment::~Fragment() {
  if (nullptr != str_) {
    XFC_DELETE(str_)
  }
}

void Fragment::Dump(JsonType &jsonType) {
  jsonType["offset"] = offset_;
  jsonType["len"] = len_;
  jsonType["conf"] = confidence_.GetScore();
  jsonType["strategy"] = (size_t)strategy_;
}

}}}
