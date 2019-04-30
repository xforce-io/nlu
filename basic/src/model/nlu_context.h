#pragma once

#include "../public.h"
#include "fragment/manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext {
 public:
  explicit NluContext(const std::wstring &query); 

  const std::wstring& GetQuery() const { return query_; }

  inline void SetSegments(const Segment::Set &segments);
  inline void SetChunkSeps(const ChunkSep::Set &chunkSeps);
  inline void SetChunks(const Chunk::Set &chunks);

  inline const typename Segment::Set& GetSegments() const;
  inline typename Segment::Set& GetSegments();
  inline const typename ChunkSep::Set& GetChunkSeps() const;
  inline typename ChunkSep::Set& GetChunkSeps();
  inline const typename Chunk::Set& GetChunks() const;
  inline typename Chunk::Set& GetChunks();

 private:
  std::wstring query_;
  ManagerFragmentSet managerFragmentSet_;
};

void NluContext::SetSegments(const typename Segment::Set &segments) {
  managerFragmentSet_.SetSegments(segments);
}

void NluContext::SetChunkSeps(const ChunkSep::Set &chunkSeps) {
  managerFragmentSet_.SetChunkSeps(chunkSeps);
}

void NluContext::SetChunks(const typename Chunk::Set &chunks) {
  managerFragmentSet_.SetChunks(chunks);
}

const typename Segment::Set& NluContext::GetSegments() const {
  return managerFragmentSet_.GetSegments();
}

typename Segment::Set& NluContext::GetSegments() {
  return managerFragmentSet_.GetSegments();
}

const typename ChunkSep::Set& NluContext::GetChunkSeps() const {
  return managerFragmentSet_.GetChunkSeps();
}

typename ChunkSep::Set& NluContext::GetChunkSeps() {
  return managerFragmentSet_.GetChunkSeps();
}

const typename Chunk::Set& NluContext::GetChunks() const {
  return managerFragmentSet_.GetChunks();
}

typename Chunk::Set& NluContext::GetChunks() {
  return managerFragmentSet_.GetChunks();
}

}}}
