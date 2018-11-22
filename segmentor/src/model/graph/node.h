#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Graph;

class Node {
 private:
  static const size_t kMaxLenQueries = 1000000;
  static const int kMaxNegLogPossi = 100;

 public: 
  Node(int offset, size_t len);

  inline void SetOffset(int offset); 
  inline void SetLen(size_t len);
  inline void AddPrev(Node &prev);
  inline void AddNext(Node &next);
  inline void SetBestPrev(Node &prev);
  inline void SetBestScore(double score);
  inline void SetNameEntity(ner::NameEntity &ner);

  ssize_t GetOffset() const { return offset_; }
  size_t GetLen() const { return len_; }
  std::vector<Node*>& GetPrevs() { return prevs_; }
  std::vector<Node*>& GetNexts() { return nexts_; }
  Node* GetBestPrev() { return bestPrev_; }
  double GetBestScore() { return bestScore_; }
  ner::NameEntity* GetNameEntity() { return nameEntity_; }
  inline int EndOffset() const;
  inline bool Optimized() const;
  inline bool IsBegin() const;
  inline bool IsEnd() const;
  inline bool IsSpecial() const;
  inline int GetShapeCode() const;

  std::string Str() const;

  void DumpProfile(const Graph &graph, const Node &node) const;

  inline static int GetShapeCode(int offset, size_t len);

 private:
  int offset_;
  size_t len_;

  std::vector<Node*> prevs_;
  std::vector<Node*> nexts_;
  Node *bestPrev_;
  double bestScore_;

  ner::NameEntity *nameEntity_;
};  

void Node::SetOffset(int offset) {
  offset_ = offset;
}

void Node::SetLen(size_t len) {
  len_ = len;
}

void Node::AddPrev(Node &prev) {
  prevs_.push_back(&prev);
}

void Node::AddNext(Node &next) {
  nexts_.push_back(&next);
}

void Node::SetBestPrev(Node &prev) {
  bestPrev_ = &prev;
}

void Node::SetBestScore(double score) {
  bestScore_ = score;
}

void Node::SetNameEntity(ner::NameEntity &nameEntity) {
  nameEntity_ = &nameEntity;
}

int Node::EndOffset() const {
  return offset_ + len_;
}

bool Node::Optimized() const {
  return bestPrev_ != NULL;
}

bool Node::IsBegin() const {
  return prevs_.empty();
}

bool Node::IsEnd() const {
  return nexts_.empty();
}

bool Node::IsSpecial() const {
  return IsBegin() || IsEnd();
}

int Node::GetShapeCode() const {
  return GetShapeCode(GetOffset(), GetLen());
}

int Node::GetShapeCode(int offset, size_t len) {
  return offset * kMaxLenQueries + len; 
}

}}}
