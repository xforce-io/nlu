#include "../parser_common.h"

namespace xforce { namespace nlu { namespace chunker {

void ParserCommon::Process(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next,
        int chunkPos,
        basic::SyntaxTag::Type::Val syntaxTag) {
  auto &chunkSeps = nluContext.GetChunkSeps();
  auto &chunks = nluContext.GetChunks();
  if (-1 == chunkPos) {
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(cur->GetOffset()));
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(cur->GetEnd()));
    if (basic::SyntaxTag::Type::kUndef != syntaxTag) {
      chunks.Add(std::make_shared<basic::Chunk>(
              syntaxTag,
              cur->GetOffset(),
              cur->GetLen(),
              320));
    }
  } else if (-2 == chunkPos) {
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(next->GetOffset()));
  } else if (-3 == chunkPos) {
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(cur->GetOffset()));
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(next->GetEnd()));
    if (basic::SyntaxTag::Type::kUndef != syntaxTag) {
      chunks.Add(std::make_shared<basic::Chunk>(
              syntaxTag,
              cur->GetOffset(),
              cur->GetLen() + next->GetLen(),
              321));
    }
  } else if (chunkPos>0) {
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(cur->GetOffset()));
    chunkSeps.Add(std::make_shared<basic::ChunkSep>(cur->GetOffset() + chunkPos));
    if (basic::SyntaxTag::Type::kUndef != syntaxTag) {
      chunks.Add(std::make_shared<basic::Chunk>(
              syntaxTag,
              cur->GetOffset(),
              chunkPos,
              322));
    }
  }


}

}}}
