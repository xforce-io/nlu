#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace chunker {

class ParserCommon {
 public:
  enum ChunkPos {
      k01,
      k1,
      k02,
      kUndef
  };

 public:
  static void Process(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next,
          ChunkPos chunkPos);
};

}}}
