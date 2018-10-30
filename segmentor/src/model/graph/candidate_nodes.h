#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Node;  

class CandidateNodes {
 private: 
  typedef std::vector<std::pair<Node*, bool>> Items;
  typedef std::tr1::unordered_map<int, size_t> Map; 
  typedef std::tr1::unordered_map<int, std::list<Node*>*> EndToNode;

 public:
  void AddNode(Node &node, bool hiConvinced);
  inline void AddNode(Node &node);
  void EstablishPrevs();
  const Items& GetItems() const { return items_; }
  inline size_t GetLen() const;

  virtual ~CandidateNodes();
 
 private: 
  void AddEndToNode_(Node &node);
  void AddEndToNode_(int end, Node &node);
  void RemoveEndToNode_(const Node &node);

 private: 
   /*
    * (node, is high convinced)
    */
  Items items_; 

   /*
    * shape code -> index
    */
  Map map_;

  EndToNode endToNode_;
};

void CandidateNodes::AddNode(Node &node) {
  AddNode(node, false);
}

size_t CandidateNodes::GetLen() const {
  return items_.size();
}

}}
