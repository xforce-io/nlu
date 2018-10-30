#pragma once

#include "public.h"
#include "../../data/manager.h"

namespace xforce { namespace nlu {

class Node;
class ConflictSubgraph;
class CandidateNodes;

class Graph {
 public: 
  typedef std::tr1::unordered_map<int, double> PrioredNegLogPossi;
  typedef std::tr1::unordered_set<int> OffsetProcessed;
  typedef std::queue<int> OffsetToProcess;
  typedef std::vector<int> Segment;
  typedef std::vector<NodesVec*> PosToNumNodes;
  typedef typename std::vector< std::pair<const Node*, ConflictSubgraph*> > ProfileItems;

 private: 
  static const double kSmoothFactor;
  static const int kMaxNegLogPossi;

 public:
  Graph(const std::string &query);

  void Process();
  inline void AddPrioredNegLogPossi(int offset, size_t len, double score);
  inline void AddMaxPrioredNegLogPossi(const Node &node);
  const Segment& GetSegments() const { return segments_; }
  void OutputPath() const;
  void Profile();

  virtual ~Graph();
 
 private: 
  void CreateNodes_();
  void Optimize_();
  void Optimize_(Node &curNode);
  double GetNegLogPossiForNodes_(const Node &node, const Node &curNode);
  inline void GetStrForNode_(
      IN const Node &node, 
      OUT std::string &str) const;
  void MakeResults_();
  void MakeProfileInfo_();
  void DumpProfile_();

  inline static double GetNegLogPossi_(const std::string &str, const std::string &condStr);

 private:   
  const std::string query_;

  Node *nodeBegin_; 
  Node *nodeEnd_;
  CandidateNodes *candidateNodes_;

  /*
   * shapeCode -> score
   */
  PrioredNegLogPossi prioredNegLogPossi_;
  OffsetProcessed offsetProcessed_;
  OffsetToProcess offsetToProcess_;

  Segment segments_;

  //for profile
  PosToNumNodes posToNumNodes_;
  ProfileItems profileItems_;
};

}}

#include "node.h"
#include "../../data/word_dict.h"
#include "../../data/bigram_dict.h"

namespace xforce { namespace nlu {

void Graph::AddPrioredNegLogPossi(int offset, size_t len, double score) {
  prioredNegLogPossi_.insert(std::make_pair(
        Node::GetShapeCode(offset, len), 
        score));
}

void Graph::AddMaxPrioredNegLogPossi(const Node &node) {
  prioredNegLogPossi_.insert(std::make_pair(
        node.GetShapeCode(),
        kMaxNegLogPossi));
}

void Graph::GetStrForNode_(
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

double Graph::GetNegLogPossi_(const std::string &str, const std::string &condStr) {
  double freqCondIndex = Manager::Get().GetWordDict().GetFreq(condStr);
  double possi = 1.0 / WordDict::GetCntWord();
  if (freqCondIndex>0) {
    double freqCooccur = Manager::Get().GetBigramDict().GetFreq(condStr, str);
    if (freqCooccur>0) {
      possi = freqCooccur / freqCondIndex;
    } else {
      possi = 0.0001;
    }
  } else {
    freqCondIndex = 0;
  }
  return -1 * log((1-kSmoothFactor) * possi + kSmoothFactor * freqCondIndex / WordDict::GetCntWord());
}

}}
