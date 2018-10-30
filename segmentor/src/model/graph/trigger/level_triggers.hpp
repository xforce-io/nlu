#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Trigger;  

class LevelTriggers {
 public: 
  inline void AddTrigger(Trigger &trigger); 
  inline void Process(      
      IN const Graph &graph, 
      IN const std::string &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results);
   
 private:  
  std::list<Trigger*> triggers_;
};

}}

#include "trigger.h"

namespace xforce { namespace nlu {

void LevelTriggers::AddTrigger(Trigger &trigger) {
  triggers_.push_back(&trigger);
}

void LevelTriggers::Process(      
    const Graph &graph, 
    const std::string &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
  for (auto iter = triggers_.begin(); iter != triggers_.end(); ++iter) {
    Trigger &trigger = **iter;
    trigger.Process(graph, query, offset, results);
  }
}

}}
