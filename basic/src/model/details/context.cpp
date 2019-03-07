#include "../context.h"

namespace xforce { namespace nlu { namespace basic {

Context::Context(const std::wstring &query) :
  query_(query) {}

Context::~Context() {
  XFC_DELETE(nameEntities_)
  XFC_DELETE(segments_)
}

}}}
