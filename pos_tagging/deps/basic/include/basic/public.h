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

  inline static Stage::Val GetPrev(Stage::Val stage);
};

Stage::Val Stage::GetPrev(Stage::Val stage) {
  switch (stage) {
    case kPosTag :
      return kSegment;
    case kChunk :
      return kPosTag;
    case kSyntax :
      return kChunk;
    case kEnd :
      return kSyntax;
    default :
      return kNone;
  }
}

}}}