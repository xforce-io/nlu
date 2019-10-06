#include "../parser_common.h"

namespace xforce { namespace nlu { namespace chunker {

void ParserCommon::Process(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next,
        int chunkPos,
        basic::SyntaxTag::Type::Val syntaxTag) {
  if (-1 == chunkPos) {
    nluContext.Add(basic::ChunkSep(cur->GetOffset()));
    nluContext.Add(basic::ChunkSep(cur->GetEnd()));
    if (basic::SyntaxTag::Type::kUndef != syntaxTag) {
      nluContext.Add(basic::Chunk(
              nluContext,
              syntaxTag,
              cur->GetOffset(),
              cur->GetLen(),
              320));
    }
  } else if (-2 == chunkPos) {
    nluContext.Add(basic::ChunkSep(next->GetOffset()));
  } else if (-3 == chunkPos) {
    nluContext.Add(basic::ChunkSep(cur->GetOffset()));
    nluContext.Add(basic::ChunkSep(next->GetEnd()));
    if (basic::SyntaxTag::Type::kUndef != syntaxTag) {
      nluContext.Add(basic::Chunk(
              nluContext,
              syntaxTag,
              cur->GetOffset(),
              cur->GetLen() + next->GetLen(),
              321));
    }
  } else if (chunkPos>0) {
    nluContext.Add(basic::ChunkSep(cur->GetOffset()));
    nluContext.Add(basic::ChunkSep(cur->GetOffset() + chunkPos));
    if (basic::SyntaxTag::Type::kUndef != syntaxTag) {
      nluContext.Add(basic::Chunk(
              nluContext,
              syntaxTag,
              cur->GetOffset(),
              chunkPos,
              322));
    }
  }


}

}}}
