#pragma once

#include "../../../public.h"
#include "sentence_feature.h"

namespace xforce { namespace nlu { namespace milkie {

class SentenceFeatureChunk : public SentenceFeature {
 public:
  inline explicit SentenceFeatureChunk(std::shared_ptr<basic::NluContext> nluContext);

  inline std::shared_ptr<basic::Chunk::Set> GetChunksFromOffset(ssize_t offset);
};

}}}