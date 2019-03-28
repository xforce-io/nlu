#include "../candidate_nodes.h"
#include "../node.h"

namespace xforce { namespace nlu { namespace segmentor {

void CandidateNodes::AddNode(Node &node, bool hiConvinced) {
  int shapeCode = node.GetShapeCode();
  auto iter = map_.find(shapeCode);
  if (iter == map_.end()) {
    map_.insert(std::make_pair(shapeCode, items_.size()));
    items_.push_back(std::make_pair(&node, hiConvinced));
    AddEndToNode_(node);
  } else if (hiConvinced) {
    RemoveEndToNode_(*(items_[iter->second].first));
    items_[iter->second].first = &node;
    items_[iter->second].second = true;
  }
}

void CandidateNodes::EstablishPrevs() {
  for (auto iter = items_.begin(); iter != items_.end(); ++iter) {
    int offset = (*iter).first->GetOffset();
    if (offset>=0) {
      auto iter1 = endToNode_.find(offset);
      if (iter1 != endToNode_.end()) {
        std::list<Node*> *nodes = iter1->second;
        for (auto iter2 = nodes->begin(); iter2 != nodes->end(); ++iter2) {
          iter->first->AddPrev(**iter2);
          (*iter2)->AddNext(*((*iter).first));
        }
      }
    }
  }
}

CandidateNodes::~CandidateNodes() {
  for (auto iter = endToNode_.begin(); iter != endToNode_.end(); ++iter) {
    std::list<Node*> &listNodes = *(iter->second);
    for (auto iter1 = listNodes.begin(); iter1 != listNodes.end(); ++iter1) {
      delete *iter1;
    }
    XFC_DELETE(iter->second)
  }
}

void CandidateNodes::AddEndToNode_(Node &node) {
  if (node.GetOffset() >= 0) {
    if (node.GetLen() > 0) {
      AddEndToNode_(node.EndOffset(), node);
    }
  } else { //BEGIN node
    AddEndToNode_(0, node);
  }
}

void CandidateNodes::AddEndToNode_(int end, Node &node) {
  auto iter = endToNode_.find(end);
  if (iter != endToNode_.end()) {
    iter->second->push_back(&node);
  } else {
    auto nodes = new std::list<Node*>();
    nodes->push_back(&node);
    endToNode_.insert(std::make_pair(end, nodes));
  }
}

void CandidateNodes::RemoveEndToNode_(const Node &node) {
  auto iter = endToNode_.find(node.EndOffset());
  if (iter == endToNode_.end()) {
    return;
  }

  auto nodes = iter->second;
  auto iter1 = nodes->begin();
  while (iter1 != nodes->end()) {
    if (*iter1 == &node) {
      nodes->erase(iter1);
      return;
    } else {
      ++iter1;
    }
  }
}

}}}
