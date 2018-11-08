#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class TriggerDefault : public Trigger {
 public: 
  inline void Process(
      IN const Graph &graph, 
      IN const std::wstring &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results); 

  virtual ~TriggerDefault() {}
};

void TriggerDefault::Process(
    const Graph &graph,
    const std::wstring &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
  UNUSE(graph)
  UNUSE(query)
  results.push_back(new TriggeredNodes(offset, 1));
}

}}
