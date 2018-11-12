#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Path;
class Graph;

class ConflictSubgraph {
 public: 
  ConflictSubgraph(
      Node &beginNode,
      Node &endNode);

  void GeneratePaths();
  std::vector<Path*>& GetPaths() { return paths_; }

  void DumpProfile(const Graph &graph);

  virtual ~ConflictSubgraph();

 private:  
  Node *beginNode_;
  Node *endNode_;

  std::vector<Path*> paths_; 
  std::queue<Path*> queue_;
};

}}}
