#include "../graph.h"
#include "../candidate_nodes.h"
#include "../triggered_nodes.h"
#include "../trigger/manager_triggers.h"
#include "../conflict_subgraph.h"

namespace xforce { namespace nlu {

const double Graph::kSmoothFactor = 0.1;
const int Graph::kMaxNegLogPossi = 100;

Graph::Graph(const std::string &query) :
    query_(query) {
  XFC_ASSERT(StrHelper::Str2Wstr(query_, wquery_))
  nodeBegin_ = new Node(-1, 0);
  nodeEnd_ = new Node(-1, 0);
  candidateNodes_ = new CandidateNodes();
  candidateNodes_->AddNode(*nodeBegin_);
  offsetToProcess_.push(0);

  for (size_t i=0; i <= wquery_.length() + 1; ++i) {
    posToNumNodes_.push_back(new NodesVec());
  }
  posToNumNodes_[0]->push_back(nodeBegin_);
  posToNumNodes_[wquery_.length() + 1]->push_back(nodeEnd_);
}

void Graph::Process() {
  CreateNodes_();
  candidateNodes_->EstablishPrevs();
  Optimize_();
  MakeResults_();
}

void Graph::OutputPath() const {
}

void Graph::Profile() {
  MakeProfileInfo_();
  DumpProfile_();
}

void Graph::GetStrForNode(
    const Node &node,
    std::string &str) const {
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

  std::string strNode, strCondNode;
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

  Node *bestPrev = NULL;
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
  
  if (NULL != bestPrev) {
    curNode.SetBestPrev(*bestPrev);
  }
  curNode.SetBestScore(bestScore);
} 

void Graph::MakeResults_() {
  Node *curNode = candidateNodes_->GetItems().back().first;
  while (!curNode->IsBegin()) {
    curNode = curNode->GetBestPrev();
    if (!curNode->IsBegin()) {
      offsets_.push_back(curNode->GetOffset());
    }
  }

  for (size_t i=0; i < offsets_.size()/2; ++i) {
    size_t one = i;
    ssize_t other = offsets_.size() - 1 - i;
    int tmp = offsets_[one];
    offsets_[one] = offsets_[other];
    offsets_[other] = tmp;
  }
}

void Graph::MakeProfileInfo_() {
  for (auto iter = candidateNodes_->GetItems().begin();
      iter != candidateNodes_->GetItems().end();
      ++iter) {
    if (!iter->first->IsSpecial()) {
      Node *node = iter->first;
      size_t woffset = node->GetWoffset(*this);
      size_t wlen = node->GetWlen(*this);
      for (size_t i = woffset + 1; i <= woffset + wlen; ++i) {
        posToNumNodes_[i]->push_back(node);
      }
    }
  }

  size_t curIdx = 0;
  size_t nextIdx = curIdx+1;
  while (true) {
    while (posToNumNodes_[curIdx]->size() == 1) {
      profileItems_.push_back(std::make_pair(
            (*(posToNumNodes_[curIdx]))[0],
            (ConflictSubgraph*)NULL));
      ++curIdx;
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
          (const Node*)NULL,
          conflictSubgraph));

    curIdx = nextIdx;
  }
}

void Graph::DumpProfile_() {
  for (size_t i=0; i < profileItems_.size() - 1; ++i) {
    auto curItem = profileItems_[i]; 
    auto nextItem = profileItems_[i+1];
    if (curItem.first != NULL && nextItem.first != NULL) {
      curItem.first->DumpProfile(*this, *(nextItem.first));
    } else if (curItem.first != NULL && nextItem.second != NULL) {
      nextItem.second->DumpProfile(*this);
    }
  }

  std::string strForNode;
  GetStrForNode(*(profileItems_.back().first), strForNode);
  std::cout << strForNode << std::endl;
}

}}
