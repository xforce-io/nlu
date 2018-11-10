#pragma once

#include "public.h"
#include "trigger.h"

namespace xforce { namespace nlu {

class TriggerDefault : public Trigger {
 public: 
  inline void Process(
      IN Graph &graph, 
      IN const std::wstring &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results); 

  virtual ~TriggerDefault() {}
};

void TriggerDefault::Process(
    Graph &graph,
    const std::wstring &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
  UNUSE(graph)
  UNUSE(query)
  results.push_back(new TriggeredNodes(offset, 1));
}

}}
