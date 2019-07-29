#include "../parser_common.h"

namespace xforce { namespace nlu { namespace chunker {

void ParserCommon::Process(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next,
        ChunkPos chunkPos) {
  auto &chunkSeps = nluContext.GetChunkSeps();
  if (ParserCommon::k01 == chunkPos) {
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(cur->GetOffset()));
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(cur->GetEnd()));
  } else if (ParserCommon::k1 == chunkPos) {
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(next->GetOffset()));
  } else if (ParserCommon::k02 == chunkPos) {
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(cur->GetOffset()));
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(next->GetEnd()));
  }
}

}}}
