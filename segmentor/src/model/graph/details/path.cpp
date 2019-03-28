#include "../path.h"
#include "../graph.h"
#include "../node.h"

namespace xforce { namespace nlu { namespace segmentor {

void Path::DumpProfile(const Graph &graph) {
  for (size_t i=0; i < nodes_.size() - 1; ++i) {
    Node &curNode = *(nodes_[i]);
    Node &nextNode = *(nodes_[i+1]);
    curNode.DumpProfile(graph, nextNode);
  }
}

}}}
