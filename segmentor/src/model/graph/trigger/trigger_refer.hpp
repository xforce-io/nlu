#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Graph;  
class TriggeredNodes;

class TriggerRefer : public Trigger {
 public: 
  inline void Process(      
      IN Graph &graph, 
      IN const std::wstring &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results);

  virtual ~TriggerRefer() {}
};

void TriggerRefer::Process(
    Graph &graph, 
    const std::wstring &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
  UNUSE(graph)
  UNUSE(query)  
  UNUSE(offset)
  UNUSE(results)
}

}}}
