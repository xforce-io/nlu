#pragma once

#include "../../../public.h"
#include "sentence_feature.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureChunk : public SentenceFeature {
 public:
  inline explicit SentenceFeatureChunk(std::shared_ptr<basic::NluContext> nluContext);

  inline std::shared_ptr<basic::Chunk::Set> GetChunksFromOffset(ssize_t offset);
  inline const std::shared_ptr<basic::Chunk> GetChunkAtOffset(ssize_t offset) const;
};

SentenceFeatureChunk::SentenceFeatureChunk(std::shared_ptr<basic::NluContext> nluContext) :
    SentenceFeature(nluContext) {}

std::shared_ptr<basic::Chunk::Set> SentenceFeatureChunk::GetChunksFromOffset(ssize_t offset) {
  auto chunks = std::make_shared<basic::Chunk::Set>(nluContext_->GetQuery());
  for (auto &chunk : nluContext_->GetChunks().GetAll()) {
    if (offset <= (ssize_t)chunk->GetOffset()) {
      chunks->Add(chunk);
    }
  }

  if (chunks->Size() != 0) {
    return chunks;
  }
  return nullptr;
}

const std::shared_ptr<basic::Chunk> SentenceFeatureChunk::GetChunkAtOffset(ssize_t offset) const {
  for (auto &chunk : nluContext_->GetChunks().GetAll()) {
    if (offset == (ssize_t)chunk->GetOffset()) {
      return chunk;
    }
  }
  return nullptr;
}

}}}