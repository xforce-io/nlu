#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Trigger;  

class LevelTriggers {
 public: 
  inline void AddTrigger(Trigger &trigger); 
  inline void Process(      
      IN Graph &graph, 
      IN const std::wstring &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results);

  virtual ~LevelTriggers();
   
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
    Graph &graph, 
    const std::wstring &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
  for (auto iter = triggers_.begin(); iter != triggers_.end(); ++iter) {
    Trigger &trigger = **iter;
    trigger.Process(graph, query, offset, results);
  }
}

LevelTriggers::~LevelTriggers() {
  for (auto iter = triggers_.begin(); iter != triggers_.end(); ++iter) {
    XFC_DELETE(*iter)
  }
}

}}
