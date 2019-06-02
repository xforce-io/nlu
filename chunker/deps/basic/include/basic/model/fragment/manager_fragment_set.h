#pragma once

#include "fragment_set.hpp"
#include "../segment.h"
#include "../chunk_sep.h"
#include "../chunk.h"

namespace xforce { namespace nlu { namespace basic {

class ManagerFragmentSet {
 public:
  ManagerFragmentSet(const std::wstring &query);

  inline void SetSegments(const Segment::Set &segments);
  inline void SetChunkSeps(const ChunkSep::Set &chunkSeps);
  inline void SetChunks(const Chunk::Set &chunks);

  const typename Segment::Set& GetSegments() const { return segments_; }
  typename Segment::Set& GetSegments() { return segments_; }
  const typename ChunkSep::Set& GetChunkSeps() const { return chunkSeps_; }
  typename ChunkSep::Set& GetChunkSeps() { return chunkSeps_; }
  const typename Chunk::Set& GetChunks() const { return chunks_; }
  typename Chunk::Set& GetChunks() { return chunks_; }

  void Dump(JsonType &jsonType);

 private:
  typename Segment::Set segments_;
  typename ChunkSep::Set chunkSeps_;
  typename Chunk::Set chunks_;
};

void ManagerFragmentSet::SetSegments(const Segment::Set &segments) {
  segments_ = segments;
}

void ManagerFragmentSet::SetChunkSeps(const ChunkSep::Set &chunkSeps) {
  chunkSeps_ = chunkSeps;
}

void ManagerFragmentSet::SetChunks(const Chunk::Set &chunks) {
  chunks_ = chunks;
}

}}}
