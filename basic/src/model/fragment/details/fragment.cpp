#include "../fragment.h"

namespace xforce { namespace nlu { namespace basic {

void Fragment::Dump(JsonType &jsonType) {
  jsonType["offset"] = offset_;
  jsonType["len"] = len_;
  jsonType["conf"] = confidence_.GetScore();
}

}}}