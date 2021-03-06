#pragma once

#include "../public.h"
#include "fragment/manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

class Phrase;
class CollectionSyntaxTag;

class NluContext {
 public:
  explicit NluContext(const std::wstring &query);
  virtual ~NluContext();

  const std::wstring& GetQuery() const { return query_; }

  inline void SetIsValid(bool isValid);
  inline void SetNameEntities(const NameEntity::Set &nameEntities);
  inline void SetSegments(const Segment::Set &segments);
  inline void SetChunkSeps(const ChunkSep::Set &chunkSeps);
  inline void SetChunks(const Chunk::Set &chunks);
  void AddPhrase(
          size_t from,
          size_t len,
          std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag,
          uint32_t strategy);

  inline bool Add(const std::shared_ptr<NameEntity> &nameEntity);
  inline bool Add(const std::shared_ptr<Segment> &segment);
  inline bool Add(const std::shared_ptr<ChunkSep> &chunkSep);
  inline bool Add(const std::shared_ptr<Chunk> &chunk);

  inline bool Add(const NameEntity &nameEntity);
  inline bool Add(const Segment &segment);
  inline bool Add(const ChunkSep &chunkSep);
  inline bool Add(const Chunk &chunk);

  inline void Clear();

  std::shared_ptr<NluContext> Build(size_t from, size_t to);
  std::shared_ptr<NluContext> Clone() const;
  void Reset(basic::Stage::Val stage);

  inline bool GetIsValid(bool check = false);
  inline const typename NameEntity::Set& GetNameEntities() const;
  inline typename NameEntity::Set& GetNameEntities();
  inline const typename Segment::Set& GetSegments() const;
  inline typename Segment::Set& GetSegments();
  inline const typename ChunkSep::Set& GetChunkSeps() const;
  inline typename ChunkSep::Set& GetChunkSeps();
  inline const typename Chunk::Set& GetChunks() const;
  inline typename Chunk::Set& GetChunks();
  const std::vector<Phrase>& GetPhrases() const { return phrases_; }

  inline bool HasPredPosBefore(size_t offset) const;

  void Dump(JsonType &jsonType, const NluContext *diff= nullptr) const;
  void Dump(std::string &json) const;

 private:
  std::wstring query_;
  bool isValid_;
  ManagerFragmentSet *managerFragmentSet_;

  std::vector<Phrase> phrases_;
};

void NluContext::SetIsValid(bool isValid) {
  isValid_ = isValid;
}

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

bool NluContext::Add(const std::shared_ptr<NameEntity> &nameEntity) {
  return Add(*nameEntity);
}

bool NluContext::Add(const std::shared_ptr<Segment> &segment) {
  return Add(*segment);
}

bool NluContext::Add(const std::shared_ptr<ChunkSep> &chunkSep) {
  return Add(*chunkSep);
}

bool NluContext::Add(const std::shared_ptr<Chunk> &chunk) {
  return Add(*chunk);
}

bool NluContext::Add(const NameEntity &nameEntity) {
  return managerFragmentSet_->GetNameEntities().Add(nameEntity);
}

bool NluContext::Add(const Segment &segment) {
  return managerFragmentSet_->GetSegments().Add(segment);
}

bool NluContext::Add(const ChunkSep &chunkSep) {
  auto iter = managerFragmentSet_->GetChunks().Begin();
  while (iter != managerFragmentSet_->GetChunks().End()) {
    auto next = iter;
    ++next;
    if ((*iter)->GetTag() == SyntaxTag::Type::kContNp &&
        (*iter)->GetOffset() < chunkSep.GetOffset() &&
        chunkSep.GetOffset() < (*iter)->GetEnd()) {
      managerFragmentSet_->GetChunks().Add(
              Chunk(
                      *this,
                      SyntaxTag::Type::kContNp,
                      (*iter)->GetOffset(),
                      chunkSep.GetOffset() - (*iter)->GetOffset()));
      managerFragmentSet_->GetChunks().Add(
              Chunk(
                      *this,
                      SyntaxTag::Type::kContNp,
                      chunkSep.GetOffset(),
                       (*iter)->GetEnd() - chunkSep.GetOffset()));
      managerFragmentSet_->GetChunks().Erase(iter);
    }
    iter = next;
  }
  return managerFragmentSet_->GetChunkSeps().Add(chunkSep);
}

bool NluContext::Add(const Chunk &chunk) {
  return managerFragmentSet_->GetChunks().Add(chunk);
}

bool NluContext::GetIsValid(bool check) {
  if (check) {
    for (auto &chunk : managerFragmentSet_->GetChunks().GetAll()) {
      if (chunk->ContainTag(SyntaxTag::Type::kNp) &&
          chunk->ContainTag(SyntaxTag::Type::kVp)) {
        isValid_ = false;
        break;
      }
    }
  }
  return isValid_;
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

bool NluContext::HasPredPosBefore(size_t offset) const {
  for (auto &segment : managerFragmentSet_->GetSegments().GetAll()) {
    if (segment->GetOffset() < offset &&
        PosTag::IsPredicate(segment->GetTag())) {
      return true;
    }
  }
  return false;
}

}}}
