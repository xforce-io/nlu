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
    kSemantic,
    kEnd,
  };

  inline static Stage::Val GetPrev(Stage::Val stage);
  inline static Stage::Val GetNext(Stage::Val stage);
};

Stage::Val Stage::GetPrev(Stage::Val stage) {
  switch (stage) {
    case kPosTag :
      return kSegment;
    case kChunk :
      return kPosTag;
    case kSyntax :
      return kChunk;
    case kSemantic:
      return kSyntax;
    case kEnd :
      return kSyntax;
    default :
      return kNone;
  }
}

Stage::Val Stage::GetNext(Stage::Val stage) {
  switch (stage) {
    case kNone :
      return kSegment;
    case kSegment :
      return kPosTag;
    case kPosTag :
      return kChunk;
    case kChunk :
      return kSyntax;
    case kSyntax :
      return kSemantic;
    case kSemantic :
      return kEnd;
    default :
      return kNone;
  }
}

}}}