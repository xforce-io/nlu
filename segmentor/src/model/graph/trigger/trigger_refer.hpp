#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Graph;  
class TriggeredNodes;

class TriggerRefer : public Trigger {
 public: 
  inline void Process(      
      IN const Graph &graph, 
      IN const std::string &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results);

  virtual ~TriggerRefer() {}
};

void TriggerRefer::Process(
    const Graph &graph, 
    const std::string &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
}

}}
