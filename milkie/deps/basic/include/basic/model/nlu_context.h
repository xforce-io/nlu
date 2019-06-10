#pragma once

#include "../public.h"
#include "fragment/manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext {
 public:
  explicit NluContext(const std::wstring &query);
  virtual ~NluContext();

  const std::wstring& GetQuery() const { return query_; }

  inline void SetNameEntities(const NameEntity::Set &nameEntities);
  inline void SetSegments(const Segment::Set &segments);
  inline void SetChunkSeps(const ChunkSep::Set &chunkSeps);
  inline void SetChunks(const Chunk::Set &chunks);

  inline const typename NameEntity::Set& GetNameEntities() const;
  inline typename NameEntity::Set& GetNameEntities();
  inline const typename Segment::Set& GetSegments() const;
  inline typename Segment::Set& GetSegments();
  inline const typename ChunkSep::Set& GetChunkSeps() const;
  inline typename ChunkSep::Set& GetChunkSeps();
  inline const typename Chunk::Set& GetChunks() const;
  inline typename Chunk::Set& GetChunks();

  void Dump(JsonType &jsonType);

 public:
  std::shared_ptr<NluContext> Build(
          const NluContext &nluContext,
          size_t from,
          size_t to);

 private:
  std::wstring query_;
  ManagerFragmentSet *managerFragmentSet_;
};

void NluContext::SetNameEntities(const NameEntity::Set &nameEntities) {
  managerFragmentSet_->SetNameEntities(nameEntities);
}

void NluContext::SetSegments(const typename Segment::Set &segments) {
  managerFragmentSet_->SetSegments(segments);
}

void NluContext::SetChunkSeps(const ChunkSep::Set &chunkSeps) {
  managerFragmentSet_->SetChunkSeps(chunkSeps);
}

void NluContext::SetChunks(const typename Chunk::Set &chunks) {
  managerFragmentSet_->SetChunks(chunks);
}

const typename NameEntity::Set& NluContext::GetNameEntities() const {
  return managerFragmentSet_->GetNameEntities();
}

typename NameEntity::Set& NluContext::GetNameEntities() {
  return managerFragmentSet_->GetNameEntities();
}

const typename Segment::Set& NluContext::GetSegments() const {
  return managerFragmentSet_->GetSegments();
}

typename Segment::Set& NluContext::GetSegments() {
  return managerFragmentSet_->GetSegments();
}

const typename ChunkSep::Set& NluContext::GetChunkSeps() const {
  return managerFragmentSet_->GetChunkSeps();
}

typename ChunkSep::Set& NluContext::GetChunkSeps() {
  return managerFragmentSet_->GetChunkSeps();
}

const typename Chunk::Set& NluContext::GetChunks() const {
  return managerFragmentSet_->GetChunks();
}

typename Chunk::Set& NluContext::GetChunks() {
  return managerFragmentSet_->GetChunks();
}

}}}
