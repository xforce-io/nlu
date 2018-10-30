#include "../node.h"

namespace xforce { namespace nlu {

Node::Node(int offset, size_t len) {
  offset_ = offset;
  len_ = len;
  bestPrev_ = NULL;
  bestScore_ = -1.0;
}

std::string Node::Str() const {
  std::stringstream ss;
  ss << "(" << this << "/" << offset_ << "/" << len_;
  if (NULL != bestPrev_) {
    ss << "/" << bestPrev_ << "/" << bestScore_;
  }
  ss << ")" << std::endl;
  return ss.str();
}

void Node::DumpProfile(const Graph &graph, const Node &node) const {
}

}}
