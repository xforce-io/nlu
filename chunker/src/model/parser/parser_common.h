#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace chunker {

class ParserCommon {
 public:
  static void Process(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next,
          int chunkPos,
          basic::SyntaxTag::Type::Val syntaxTag);
};

}}}
