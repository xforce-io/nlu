#pragma once

#include "fragment_set.hpp"
#include "../segment.h"
#include "../chunk.h"

namespace xforce { namespace nlu { namespace basic {

class ManagerFragmentSet {
 public:
  ManagerFragmentSet();

  const typename Segment::Set& GetSegments() const { return segments_; }
  typename Segment::Set& GetSegments() { return segments_; }
  const typename Chunk::Set& GetChunks() const { return chunks_; }
  typename Chunk::Set& GetChunks() { return chunks_; }

 private:
  typename Segment::Set segments_;
  typename Chunk::Set chunks_;
};

}}}
