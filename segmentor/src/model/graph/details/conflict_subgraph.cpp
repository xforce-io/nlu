#include "../conflict_subgraph.h"

#include "../path.h"
#include "../graph.h"

namespace xforce { namespace nlu { namespace segmentor {

ConflictSubgraph::ConflictSubgraph(
      Node &beginNode,
      Node &endNode) {
  beginNode_ = &beginNode;
  endNode_ = &endNode;

  std::vector<Node*> nexts = beginNode.GetNexts();
  for (auto iter = nexts.begin(); iter != nexts.end(); ++iter) {
    queue_.push(&Path::CreateFromNode(**iter));
  }
}

void ConflictSubgraph::GeneratePaths() {
  while (!queue_.empty()) {
    Path &thePath = *(queue_.front());
    queue_.pop();

    bool completePath = false;
    std::vector<Node*> nexts = thePath.End()->GetNexts();
    for (auto iter = nexts.begin(); iter != nexts.end(); ++iter) {
      Node &next = **iter;
      if (&next != endNode_) {
        queue_.push(&thePath.CopyAndAdd(next));
      } else {
        paths_.push_back(&thePath);
        completePath = true;
      }
    }

    if (!completePath) {
      delete &thePath;
    }
  }
}

void ConflictSubgraph::DumpProfile(const Graph &graph) {
  std::wcout << "[";  
  for (auto iter = paths_.begin(); iter != paths_.end(); ++iter) {
    Path &path = **iter;
    beginNode_->DumpProfile(graph, *path.Begin());
    path.DumpProfile(graph);
    path.End()->DumpProfile(graph, *endNode_);
    std::wcout << " | ";
  }
  std::wcout << "] -> ";
}

ConflictSubgraph::~ConflictSubgraph() {
  for (auto iter = paths_.begin(); iter != paths_.end(); ++iter) {
    XFC_DELETE(*iter)
  }

  while (!queue_.empty()) {
    XFC_DELETE(queue_.front())
    queue_.pop();
  }
}

}}}
