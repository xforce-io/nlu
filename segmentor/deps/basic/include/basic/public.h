#pragma once

#include "public/public.h"

namespace xforce { namespace nlu { namespace basic {

struct Stage {
  enum Val {
    kNone,
    kSegment,
    kPosTag,
    kChunk,
    kSyntax,
    kEnd,
  };
};

}}}