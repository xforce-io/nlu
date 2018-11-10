#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Graph;  
class TriggeredNodes;

class Trigger {
 public: 
  virtual void Process(
      IN Graph &graph, 
      IN const std::wstring &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results) = 0; 

  virtual ~Trigger() {}
};  

}}
