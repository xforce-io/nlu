#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace chunker {

class ChunkNode {
 public: 
  enum Type {
    kVp,
    kAp,
    kNp,
    kSeg,
    kUnknown,
  };

 public: 
  inline explicit ChunkNode(const basic::Segment &segment);
  inline explicit ChunkNode(const std::vector<basic::Segment> &segments);

 private:
   Type type_;
   std::list<ChunkNode*> chunkNodes_;
   basic::Segment segment_;
};

ChunkNode::ChunkNode(const basic::Segment &segment) :
    type_(kSeg),
    segment_(segment) {}

ChunkNode::ChunkNode(const std::vector<basic::Segment> &segments) :
    type_(kUnknown) {
  for (auto &segment : segments) {
    chunkNodes_.push(new ChunkNode(segment));
  }
}

}}}
