#include "../manager_fragment_set.h"

namespace xforce { namespace nlu { namespace basic {

ManagerFragmentSet::ManagerFragmentSet(const std::wstring &query) :
    query_(query),
    nameEntities_(query),
    segments_(query),
    chunkSeps_(query),
    chunks_(query) {}

void ManagerFragmentSet::Dump(JsonType &jsonType) {
  nameEntities_.Dump(jsonType["nameEntities"]);
  segments_.Dump(jsonType["seg"]);
  chunkSeps_.Dump(jsonType["chunkSep"]);
  chunks_.Dump(jsonType["chunk"]);
}

ManagerFragmentSet* ManagerFragmentSet::Build(
        size_t from,
        size_t to) {
  if (from >= to || from >= query_.length() || to >= query_.length()) {
    return nullptr;
  }

  ManagerFragmentSet *result = new ManagerFragmentSet(query_.substr(from, to-from));
  for (auto nameEntity : nameEntities_.GetAll()) {
    if (nameEntity->GetBegin() >= from && nameEntity->GetEnd() <= to) {
      result->nameEntities_.Add(nameEntity);
    }
  }

  for (auto segment : segments_.GetAll()) {
    if (segment->GetBegin() >= from && segment->GetEnd() <= to) {
      result->segments_.Add(segment);
    }
  }

  for (auto chunkSep : chunkSeps_.GetAll()) {
    if (chunkSep->GetBegin() >= from && chunkSep->GetEnd() <= to) {
      result->chunkSeps_.Add(chunkSep);
    }
  }

  for (auto chunk : chunks_.GetAll()) {
    if (chunk->GetBegin() >= from && chunk->GetEnd() <= to) {
      result->chunks_.Add(chunk);
    }
  }
  return result;
}

}}}
