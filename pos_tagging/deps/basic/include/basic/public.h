#pragma once

#include "public/public.h"

namespace xforce { namespace nlu { namespace basic {

struct Stage {
  enum Type {
    kNone,
    kSegment,
    kPosTag,
    kChunk,
    kSyntax,
    kEnd,
  };
};

}}}