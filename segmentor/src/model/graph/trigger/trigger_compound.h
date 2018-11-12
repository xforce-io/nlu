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
};

}}}
