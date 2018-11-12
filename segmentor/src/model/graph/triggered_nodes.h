#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class TriggeredNodes {
 public:
  explicit TriggeredNodes(Node *singleNode);
  TriggeredNodes();
  TriggeredNodes(int offset, size_t length);

  inline Node& AddNode(int offset, size_t len);
  inline void AddNode(Node &node);
  inline const Node& GetNode() const;
  inline std::vector<Node*> &GetNodes() { return nodes_; }
  inline size_t GetLen() const { return len_; }
  inline int GetEndOffset() const { return endOffset_; }

  std::string Str() const;

 private:   
  std::vector<Node*> nodes_;
  size_t len_;
  int endOffset_;
};  

}}}

#include "node.h"

namespace xforce { namespace nlu { namespace segmentor {

Node& TriggeredNodes::AddNode(int offset, size_t len) {
  Node *node = new Node(offset, len);
  AddNode(*node);
  return *node;
}

void TriggeredNodes::AddNode(Node &node) {
  nodes_.push_back(&node);
  len_ += node.GetLen();
  if (node.EndOffset() > endOffset_) {
    endOffset_ = node.EndOffset();
  }
}

const Node& TriggeredNodes::GetNode() const {
  return *(nodes_[0]);
}

}}}
