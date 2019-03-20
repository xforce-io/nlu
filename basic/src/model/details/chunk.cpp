#include "../chunk.h"

namespace xforce { namespace nlu { namespace basic {

Chunk::~Chunk() {
  XFC_DELETE(str_)
}

}}}
