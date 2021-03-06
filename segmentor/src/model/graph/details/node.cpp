#include "../node.h"

#include "../graph.h"

namespace xforce { namespace nlu { namespace segmentor {

Node::Node(int offset, size_t len) {
  offset_ = offset;
  len_ = len;
  bestPrev_ = nullptr;
  bestScore_ = -1.0;
  nameEntity_ = nullptr;
  posTag_ = basic::PosTag::Type::kUndef;
}

Node::Node(
    int offset,
    size_t len,
    basic::PosTag::Type::Val posTag) :
  Node(offset, len) {
  SetPosTag(posTag);
}

std::string Node::Str() const {
  std::stringstream ss;
  ss << "(" << this << "/" << offset_ << "/" << len_;
  if (nullptr != bestPrev_) {
    ss << "/" << bestPrev_ << "/" << bestScore_;
  }
  ss << ")";
  return ss.str();
}

void Node::DumpProfile(const Graph &graph, const Node &nextNode) const {
  std::wstring strForNode;
  graph.GetStrForNode(*this, strForNode);
  std::wcout << strForNode 
      << L" =" 
      << graph.GetNegLogPossiForNodes(nextNode, *this) 
      << L"=>";
}

}}}
