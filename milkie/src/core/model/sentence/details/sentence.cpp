#include "../sentence.h"

namespace xforce { namespace nlu { namespace milkie {

Sentence::~Sentence() {
  XFC_DELETE(featureSegment_)
  XFC_DELETE(featureContent_)
}

}}}
