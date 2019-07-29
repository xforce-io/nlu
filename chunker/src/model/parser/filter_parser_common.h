#pragma once

#include "parser_common.h"

namespace xforce { namespace nlu { namespace chunker {

class FilterParserCommon {
 public:
  FilterParserCommon() {}
  virtual ~FilterParserCommon() {}

  virtual ParserCommon::ChunkPos Filter(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next) = 0;
};

class FPCDongqu : public FilterParserCommon {
 public:
  ParserCommon::ChunkPos Filter(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next);
};

class FPCMid : public FilterParserCommon {
 public:
  ParserCommon::ChunkPos Filter(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next);
};

class FPCSurround : public FilterParserCommon {
 public:
  ParserCommon::ChunkPos Filter(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next);
};

}}}
