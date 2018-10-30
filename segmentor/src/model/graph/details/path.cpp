#include "../path.h"
#include "../graph.h"
#include "../node.h"

namespace xforce { namespace nlu {

Path& Path::DumpProfile(const Graph &graph) {
  Path *path = new Path();
  for (size_t i=0; i < nodes_.size(); ++i) {
    Node &curNode = *(nodes_[i]);
    Node &nextNode = *(nodes_[i+1]);
    curNode.DumpProfile(graph, nextNode);
  }
  return *path;
}

}}
