#include "../context.h"

namespace xforce { namespace nlu { namespace basic {

Context::Context(const std::wstring &query) :
  query_(query),
  segments_(nullptr),
  nameEntities_(nullptr) {}

Context::~Context() {
  XFC_DELETE(nameEntities_)
  XFC_DELETE(segments_)
}

}}}
