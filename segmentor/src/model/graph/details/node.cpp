#include "../node.h"

#include "../graph.h"

namespace xforce { namespace nlu {

Node::Node(int offset, size_t len) {
  offset_ = offset;
  len_ = len;
  bestPrev_ = NULL;
  bestScore_ = -1.0;
}

size_t Node::GetWoffset(const Graph &graph) const {
  std::wstring wstr;
  XFC_ASSERT(StrHelper::Str2Wstr(graph.GetQuery().substr(0, offset_), wstr))
  return wstr.length();
}

size_t Node::GetWlen(const Graph &graph) const {
  std::wstring wstr;
  XFC_ASSERT(StrHelper::Str2Wstr(graph.GetQuery().substr(offset_, len_), wstr))
  return wstr.length();
}

std::string Node::Str() const {
  std::stringstream ss;
  ss << "(" << this << "/" << offset_ << "/" << len_;
  if (NULL != bestPrev_) {
    ss << "/" << bestPrev_ << "/" << bestScore_;
  }
  ss << ")";
  return ss.str();
}

void Node::DumpProfile(const Graph &graph, const Node &nextNode) const {
  std::string strForNode;
  graph.GetStrForNode(*this, strForNode);
  std::cout << strForNode 
      << " =" 
      << graph.GetNegLogPossiForNodes(nextNode, *this) 
      << "=>";
}

}}
