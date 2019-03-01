#include "../graph.h"
#include "../candidate_nodes.h"
#include "../triggered_nodes.h"
#include "../trigger/manager_triggers.h"
#include "../conflict_subgraph.h"

namespace xforce { namespace nlu { namespace segmentor {

const double Graph::kSmoothFactor = 0.1;
const int Graph::kMaxNegLogPossi = 100;

Graph::Graph(const std::wstring &query) :
    query_(query) {
  nodeBegin_ = new Node(-1, 0);
  nodeEnd_ = new Node(-1, 0);
  candidateNodes_ = new CandidateNodes();
  candidateNodes_->AddNode(*nodeBegin_);
  offsetToProcess_.push(0);

  for (size_t i=0; i <= query_.length() + 1; ++i) {
    posToNumNodes_.push_back(new NodesVec());
  }
  posToNumNodes_[0]->push_back(nodeBegin_);
  posToNumNodes_[query_.length() + 1]->push_back(nodeEnd_);
}

void Graph::Process(basic::FragmentSet &segments, basic::FragmentSet &nameEntities) {
  CreateNodes_();
  candidateNodes_->EstablishPrevs();
  Optimize_();
  MakeResults_(segments, nameEntities);
}

void Graph::Profile(basic::FragmentSet &segments, basic::FragmentSet &nameEntities) {
  Process(segments, nameEntities);
  MakeProfileInfo_();
  DumpProfile_();
}

void Graph::GetStrForNode(
    const Node &node,
    std::wstring &str) const {
  if (!node.IsSpecial()) {
    str.assign(query_.substr(node.GetOffset(), node.GetLen()));
  } else if (node.IsBegin()) {
    str.assign(kMarkStart);
  } else {
    str.assign(kMarkEnd);
  }
}

double Graph::GetNegLogPossiForNodes(const Node &node, const Node &condNode) const {
  auto iter = prioredNegLogPossi_.find(node.GetShapeCode(
        condNode.GetOffset(),
        condNode.GetLen() + node.GetLen()));
  if (iter != prioredNegLogPossi_.end()) {
    return iter->second;
  }

  std::wstring strNode, strCondNode;
  GetStrForNode(node, strNode);
  GetStrForNode(condNode, strCondNode);
  return GetNegLogPossi_(strNode, strCondNode);
}

Graph::~Graph() {
  for (auto iter = profileItems_.begin(); iter != profileItems_.end(); ++iter) {
    XFC_DELETE(iter->second)
  }
  for (auto iter = posToNumNodes_.begin(); iter != posToNumNodes_.end(); ++iter) {
    XFC_DELETE(*iter)
  }
  XFC_DELETE(candidateNodes_)
  XFC_DELETE(nodeEnd_)  
}

void Graph::CreateNodes_() {
  std::list<TriggeredNodes*> tmpContinousNodes;
  while (!offsetToProcess_.empty()) {
    int offset = offsetToProcess_.front();
    offsetToProcess_.pop();
    if (offsetProcessed_.find(offset) == offsetProcessed_.end()) {
      tmpContinousNodes.clear();
      ManagerTriggers::Get().Process(*this, query_, offset, tmpContinousNodes);
      for (auto iter = tmpContinousNodes.begin();
          iter != tmpContinousNodes.end();
          ++iter) {
        TriggeredNodes *continuousNode = *iter;
        for (auto iter1 = continuousNode->GetNodes().begin();
            iter1 != continuousNode->GetNodes().end();
            ++iter1) {
          candidateNodes_->AddNode(**iter1);
        }

        if (offset + continuousNode->GetLen() != query_.length()) {
          offsetToProcess_.push(continuousNode->GetEndOffset());
        }
        XFC_DELETE(continuousNode)
      } 
      offsetProcessed_.insert(offset);
    }
  }
  nodeEnd_->SetOffset(query_.length());
  candidateNodes_->AddNode(*nodeEnd_);
}

void Graph::Optimize_() {
  Optimize_(*(candidateNodes_->GetItems().back().first));
}

void Graph::Optimize_(Node &curNode) {
  if (curNode.IsBegin()) {
    return;
  }

  Node *bestPrev = nullptr;
  double bestScore = std::numeric_limits<double>::max();
  for (auto iter = curNode.GetPrevs().begin();
      iter != curNode.GetPrevs().end();
      ++iter) {
    Node &prevNode = **iter;
    if (!prevNode.Optimized()) {
      Optimize_(prevNode);
    }

    double thePathScore = prevNode.GetBestScore() + GetNegLogPossiForNodes(curNode, prevNode);
    if (thePathScore < bestScore) {
      bestScore = thePathScore;
      bestPrev = &prevNode;
    }
  }
  
  if (nullptr != bestPrev) {
    curNode.SetBestPrev(*bestPrev);
  }
  curNode.SetBestScore(bestScore);
} 

void Graph::MakeResults_(basic::FragmentSet &segments, basic::FragmentSet &nameEntities) {
  std::vector<basic::Segment> tmpSegments;

  Node *curNode = candidateNodes_->GetItems().back().first;
  while (!curNode->IsBegin()) {
    curNode = curNode->GetBestPrev();
    if (curNode->GetNameEntity() != nullptr) {
      nameEntities.Add(curNode->GetNameEntity());
    }

    if (!curNode->IsBegin()) {
      basic::Segment segment = basic::Segment(curNode->GetOffset());
      if (curNode->GetPos() != basic::Pos::kUndef) {
        segment.SetPos(curNode->GetPos());
      }
      tmpSegments.push_back(segment);
    }
  }

  for (size_t i=0; i < tmpSegments.size()/2; ++i) {
    size_t one = i;
    ssize_t other = tmpSegments.size() - 1 - i;
    basic::Segment tmp = tmpSegments[one];
    tmpSegments[one] = tmpSegments[other];
    tmpSegments[other] = tmp;
  }

  for (size_t i=1; i < tmpSegments.size(); ++i) {
    tmpSegments[i-1].SetLen(tmpSegments[i].GetOffset() - tmpSegments[i-1].GetOffset());
  }

  basic::Segment &lastSegment = tmpSegments[tmpSegments.size() - 1];
  lastSegment.SetLen(query_.length() - lastSegment.GetOffset());

  for (auto &segment : tmpSegments) {
    segments.Add(segment);
  }
}

void Graph::MakeProfileInfo_() {
  for (auto iter = candidateNodes_->GetItems().begin();
      iter != candidateNodes_->GetItems().end();
      ++iter) {
    if (!iter->first->IsSpecial()) {
      Node *node = iter->first;
      size_t woffset = node->GetOffset();
      size_t wlen = node->GetLen();
      for (size_t i = woffset + 1; i <= woffset + wlen; ++i) {
        posToNumNodes_[i]->push_back(node);
      }
    }
  }

  size_t curIdx = 0;
  size_t nextIdx = curIdx+1;
  while (true) {
    while (posToNumNodes_[curIdx]->size() == 1) {
      Node *node = (*(posToNumNodes_[curIdx]))[0];
      profileItems_.push_back(std::make_pair(
            node,
            (ConflictSubgraph*)nullptr));

      size_t curNodeLen = node->GetLen();
      int curNodeOffset = node->GetOffset();
      if (curNodeOffset > 0 && curNodeLen != 0) {
        curIdx += curNodeLen;
      } else {
        ++curIdx;
      }

      if (curIdx >= posToNumNodes_.size()) {
        return;
      }
    }

    nextIdx = curIdx+1;
    --curIdx;
    while (posToNumNodes_[nextIdx]->size() != 1) {
      ++nextIdx;
    }

    ConflictSubgraph *conflictSubgraph = new ConflictSubgraph(
        *((*posToNumNodes_[curIdx])[0]),
        *((*posToNumNodes_[nextIdx])[0]));
    conflictSubgraph->GeneratePaths();
    profileItems_.push_back(std::make_pair(
          (const Node*)nullptr,
          conflictSubgraph));

    curIdx = nextIdx;
  }
}

void Graph::DumpProfile_() {
  for (size_t i=0; i < profileItems_.size() - 1; ++i) {
    auto curItem = profileItems_[i]; 
    auto nextItem = profileItems_[i+1];
    if (curItem.first != nullptr && nextItem.first != nullptr) {
      curItem.first->DumpProfile(*this, *(nextItem.first));
    } else if (curItem.first != nullptr && nextItem.second != nullptr) {
      nextItem.second->DumpProfile(*this);
    }
  }

  std::wstring strForNode;
  GetStrForNode(*(profileItems_.back().first), strForNode);
  std::wcout << strForNode << std::endl;
}

}}}
