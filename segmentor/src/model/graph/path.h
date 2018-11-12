#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Graph;  
class Node;

class Path {
 public:
  inline void AddNode(Node &node);
  inline Node* Begin();
  inline Node* End();
  inline bool NonEmpty();
  inline Path& CopyAndAdd(Node &node);

  void DumpProfile(const Graph &graph);

  inline static Path& CreateFromNode(Node &node);

 private:  
  std::vector<Node*> nodes_;
};

void Path::AddNode(Node &node) {
  nodes_.push_back(&node);
}

Node* Path::Begin() {
  if (!nodes_.empty()) {
    return nodes_.front();
  } else {
    return NULL;
  }
}

Node* Path::End() {
  if (!nodes_.empty()) {
    return nodes_[nodes_.size() - 1];
  } else {
    return NULL;
  }
}

bool Path::NonEmpty() {
  return nodes_.empty();
}

Path& Path::CopyAndAdd(Node &node) {
  Path *path = new Path();
  for (size_t i=0; i < nodes_.size(); ++i) {
    path->AddNode(*nodes_[i]);
  }
  path->AddNode(node);
  return *path;
}

Path& Path::CreateFromNode(Node &node) {
  Path *path = new Path();
  path->AddNode(node);
  return *path;
}

}}}
