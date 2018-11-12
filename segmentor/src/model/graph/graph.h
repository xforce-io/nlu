#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Node;
class ConflictSubgraph;
class CandidateNodes;

class Graph {
 public: 
  typedef std::tr1::unordered_map<int, double> PrioredNegLogPossi;
  typedef std::tr1::unordered_set<int> OffsetProcessed;
  typedef std::queue<int> OffsetToProcess;
  typedef std::vector<size_t> Offset;
  typedef std::vector<NodesVec*> PosToNumNodes;
  typedef typename std::vector< std::pair<const Node*, ConflictSubgraph*> > ProfileItems;

 private: 
  static const double kSmoothFactor;
  static const int kMaxNegLogPossi;

 public:
  explicit Graph(const std::wstring &query);

  void Process();
  inline void AddPrioredNegLogPossi(int offset, size_t len, double score);
  inline void AddMaxPrioredNegLogPossi(const Node &node);
  const Offset& GetOffsets() const { return offsets_; }
  void OutputPath() const;
  void Profile();

  const std::wstring& GetQuery() const { return query_; }
  void GetStrForNode(
      IN const Node &node, 
      OUT std::wstring &str) const;
  double GetNegLogPossiForNodes(
      const Node &node, 
      const Node &curNode) const;

  virtual ~Graph();
 
 private: 
  void CreateNodes_();
  void Optimize_();
  void Optimize_(Node &curNode);
  void MakeResults_();
  void MakeProfileInfo_();
  void DumpProfile_();

  inline static double GetNegLogPossi_(const std::wstring &str, const std::wstring &condStr);

 private:   
  std::wstring query_;

  Node *nodeBegin_; 
  Node *nodeEnd_;
  CandidateNodes *candidateNodes_;

  /*
   * shapeCode -> score
   */
  PrioredNegLogPossi prioredNegLogPossi_;
  OffsetProcessed offsetProcessed_;
  OffsetToProcess offsetToProcess_;

  Offset offsets_;

  //for profile
  PosToNumNodes posToNumNodes_;
  ProfileItems profileItems_;
};

}}}

#include "node.h"
#include "../../data/word_dict.h"
#include "../../data/bigram_dict.h"
#include "../../data/manager.h"

namespace xforce { namespace nlu { namespace segmentor {

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

double Graph::GetNegLogPossi_(const std::wstring &str, const std::wstring &condStr) {
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

}}}
