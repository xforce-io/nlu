#pragma once

#include "../public.h"
#include "trigger.h"

namespace xforce { namespace nlu { namespace segmentor {

class Graph;  
class TriggeredNodes;

class TriggerCompound : public Trigger {
 private:
  static const wchar_t kMarkPunction = L'、';

 public: 
  void Process(      
      IN Graph &graph, 
      IN const std::wstring &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results);

  virtual ~TriggerCompound() {}
 
 private: 
  inline Node* AddNewPersonName_(
      const std::wstring &query, 
      TriggeredNodes &triggeredNodes, 
      int offset, 
      size_t len);
};

}}}

#include "../node.h"
#include "../triggered_nodes.h"

namespace xforce { namespace nlu { namespace segmentor {

Node* TriggerCompound::AddNewPersonName_(
    const std::wstring &query,
    TriggeredNodes &triggeredNodes, 
    int offset, 
    size_t len) {
  auto newNode = new Node(offset, len);
  newNode->SetNameEntity(
      std::shared_ptr<ner::NameEntity>(
          new ner::PersonName(query.substr(offset, len), offset)));
  triggeredNodes.AddNode(*newNode);
  return newNode;
}

}}}
