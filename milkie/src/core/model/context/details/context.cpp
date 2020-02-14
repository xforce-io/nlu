#include "../context.h"

namespace xforce { namespace nlu { namespace milkie {

Context::~Context() {
  XFC_DELETE(sentence_)
}

void Context::Dump(JsonType &jsonType) {
  jsonType["startPos"] = (int64_t)startPos_;
  jsonType["curPos"] = (int64_t)curPos_;
  storage_.Dump(jsonType["storage"]);
}

}}}
