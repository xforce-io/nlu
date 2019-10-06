#pragma once

#include "../public.h"
#include "fragment/manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

class Phrase;

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
          size_t to,
          std::shared_ptr<NluContext> &nluContext);

  inline bool Add(const NameEntity &nameEntity);
  inline bool Add(const Segment &segment);
  inline bool Add(const ChunkSep &chunkSep);
  inline bool Add(const Chunk &chunk);

  std::shared_ptr<NluContext> Build(size_t from, size_t to);
  std::shared_ptr<NluContext> Clone() const;
  void Reset(basic::Stage::Val stage);

  inline bool GetIsValid() const;
  inline const typename NameEntity::Set& GetNameEntities() const;
  inline const typename Segment::Set& GetSegments() const;
  inline const typename ChunkSep::Set& GetChunkSeps() const;
  inline const typename Chunk::Set& GetChunks() const;

  inline bool HasPredPosBefore(size_t offset) const;

  void Dump(JsonType &jsonType);
  void Dump(std::string &json);

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

bool NluContext::Add(const NameEntity &nameEntity) {
  managerFragmentSet_->GetNameEntities().Add(nameEntity);
}

bool NluContext::Add(const Segment &segment) {
  managerFragmentSet_->GetSegments().Add(segment);
}

bool NluContext::Add(const ChunkSep &chunkSep) {
  bool ret = managerFragmentSet_->GetChunkSeps().Add(chunkSep);
  if (ret) {
    JsonType jsonType;
    jsonType["name"] = "add";
    chunkSep.Dump(jsonType);
    AnalysisTracer::Get()->AddEvent(jsonType);
  }
  return ret;
}

bool NluContext::Add(const Chunk &chunk) {
  bool ret = managerFragmentSet_->GetChunks().Add(chunk);
  if (ret) {
    JsonType jsonType;
    jsonType["name"] = "add";
    chunkSep.Dump(jsonType);
    AnalysisTracer::Get()->AddEvent(jsonType);
  }
  return ret;
}

bool NluContext::GetIsValid() const {
  return isValid_;
}

const typename NameEntity::Set& NluContext::GetNameEntities() const {
  return managerFragmentSet_->GetNameEntities();
}

const typename Segment::Set& NluContext::GetSegments() const {
  return managerFragmentSet_->GetSegments();
}

const typename ChunkSep::Set& NluContext::GetChunkSeps() const {
  return managerFragmentSet_->GetChunkSeps();
}

const typename Chunk::Set& NluContext::GetChunks() const {
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
