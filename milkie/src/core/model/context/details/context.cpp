#include "../context.h"

namespace xforce { namespace nlu { namespace milkie {

Context::~Context() {
  XFC_DELETE(sentence_)
}

}}}
