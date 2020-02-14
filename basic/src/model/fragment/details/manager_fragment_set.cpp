#include "../manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

ManagerFragmentSet::ManagerFragmentSet(const std::wstring &query) :
    query_(query),
    nameEntities_(query),
    segments_(query),
    chunkSeps_(query),
    chunks_(query) {}

void ManagerFragmentSet::Dump(
        JsonType &jsonType,
        const ManagerFragmentSet *managerFragmentSet) const {
  nameEntities_.Dump(
          jsonType,
          nullptr != managerFragmentSet ? &(managerFragmentSet->nameEntities_) : nullptr);

  segments_.Dump(
          jsonType,
          nullptr != managerFragmentSet ? &(managerFragmentSet->segments_) : nullptr);

  chunkSeps_.Dump(
          jsonType,
          nullptr != managerFragmentSet ? &(managerFragmentSet->chunkSeps_) : nullptr);

  chunks_.Dump(
          jsonType,
          nullptr != managerFragmentSet ? &(managerFragmentSet->chunks_) : nullptr);
}

ManagerFragmentSet* ManagerFragmentSet::Build(
        size_t from,
        size_t to) {
  if (from >= to || from >= query_.length() || to > query_.length()) {
    return nullptr;
  }

  ManagerFragmentSet *result = new ManagerFragmentSet(query_.substr(from, to-from));
  for (auto nameEntity : nameEntities_.GetAll()) {
    if (nameEntity->GetBegin() >= from && nameEntity->GetEnd() <= to) {
      auto newNameEntity = std::make_shared<basic::NameEntity>(*nameEntity);
      newNameEntity->SetOffset(nameEntity->GetOffset() - from);
      result->nameEntities_.Add(newNameEntity);
    }
  }

  for (auto segment : segments_.GetAll()) {
    if (segment->GetBegin() >= from && segment->GetEnd() <= to) {
      auto newSeg = std::make_shared<basic::Segment>(*segment);
      newSeg->SetOffset(segment->GetOffset() - from);
      result->segments_.Add(newSeg);
    }
  }

  for (auto chunkSep : chunkSeps_.GetAll()) {
    if (chunkSep->GetBegin() >= from && chunkSep->GetEnd() <= to) {
      auto newChunkSep = std::make_shared<basic::ChunkSep>(*chunkSep);
      newChunkSep->SetOffset(chunkSep->GetOffset() - from);
      result->chunkSeps_.Add(newChunkSep);
    }
  }

  for (auto chunk : chunks_.GetAll()) {
    if (chunk->GetBegin() >= from && chunk->GetEnd() <= to) {
      auto newChunk = std::make_shared<basic::Chunk>(*chunk);
      newChunk->SetOffset(chunk->GetOffset() - from);
      result->chunks_.Add(newChunk);
    }
  }
  return result;
}

ManagerFragmentSet* ManagerFragmentSet::Clone() {
  auto managerFragmentSet = new ManagerFragmentSet(query_);
  managerFragmentSet->SetNameEntities(nameEntities_);
  managerFragmentSet->SetSegments(segments_);
  managerFragmentSet->SetChunkSeps(chunkSeps_);
  managerFragmentSet->SetChunks(chunks_);
  return managerFragmentSet;
}

}}}
