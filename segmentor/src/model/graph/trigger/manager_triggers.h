#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Graph;
class TriggeredNodes;
class LevelTriggers;

class ManagerTriggers {
 public: 
  ManagerTriggers(); 

  void Process(      
    IN Graph &graph, 
    IN const std::wstring &query, 
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

}}}
