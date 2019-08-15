#pragma once

#include "parser_common.h"

namespace xforce { namespace nlu { namespace chunker {

class FilterParserCommon {
 public:
  FilterParserCommon() {}
  virtual ~FilterParserCommon() {}

  // @return :
  //     ==0 => undef
  //      -1 => | cur | next
  //      -2 =>   cur | next
  //      -3 => | cur   next |
  //      >0 => | <-cur--offset--> |
  virtual void Filter(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next,
          int &chunkPos,
          basic::SyntaxTag::Type::Val &syntaxTag) = 0;
};

class FPCDongjieAndDongqu : public FilterParserCommon {
 public:
  void Filter(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next,
          int &chunkPos,
          basic::SyntaxTag::Type::Val &syntaxTag);
};

class FPCMid : public FilterParserCommon {
 public:
  void Filter(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next,
          int &chunkPos,
          basic::SyntaxTag::Type::Val &syntaxTag);
};

class FPCSurround : public FilterParserCommon {
 public:
  void Filter(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> cur,
          std::shared_ptr<basic::Segment> next,
          int &chunkPos,
          basic::SyntaxTag::Type::Val &syntaxTag);
};

}}}
