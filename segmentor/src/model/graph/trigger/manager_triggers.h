#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Graph;
class TriggeredNodes;
class LevelTriggers;

class ManagerTriggers {
 public: 
  ManagerTriggers(); 

  void Process(      
    IN const Graph &graph, 
    IN const std::string &query, 
    IN int offset, 
    OUT std::list<TriggeredNodes*> &results);

  virtual ~ManagerTriggers();

  inline static ManagerTriggers &Get();
  static void Tini();
 
 private:
  std::list<LevelTriggers*> levelTriggers_;

  static ManagerTriggers *managerTriggers_;
};

ManagerTriggers &ManagerTriggers::Get() {
  return *managerTriggers_;
}

}}
