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

  size_t accuLen = 0;
  bool mark = false;
  for (auto &chunk : nluContext_->GetChunks().GetAll()) {
    if (offset == (ssize_t)accuLen) {
      mark = true;
    }

    if (mark) {
      chunks->Add(chunk);
    }
    accuLen += chunk->GetLen();
  }

  if (mark) {
    return chunks;
  }
  return nullptr;
}

const std::shared_ptr<basic::Chunk> SentenceFeatureChunk::GetChunkAtOffset(ssize_t offset) const {
  ssize_t accuLen = 0;
  for (auto &chunk : nluContext_->GetChunks().GetAll()) {
    if (offset == accuLen) {
      return chunk;
    }
    accuLen += chunk->GetLen();
  }
  return nullptr;
}

}}}