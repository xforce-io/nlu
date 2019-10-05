#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Graph;
class TriggeredNodes;

class TriggerPrefix : public Trigger {
 public: 
  inline void Process(      
      IN Graph &graph, 
      IN const std::wstring &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results);

  virtual ~TriggerPrefix() {}
};

}}}

#include "../../../data/manager.h"
#include "../../core_dict_item.h"
#include "../../../data/word_dict.h"
#include "../triggered_nodes.h"

namespace xforce { namespace nlu { namespace segmentor {

void TriggerPrefix::Process(      
    Graph &graph, 
    const std::wstring &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
  UNUSE(graph)
  std::vector<const CoreDictItem*> coreDictItems;
  Manager::Get().GetWordDict().PrefixMatch(
      query.substr(offset),
      coreDictItems);
  if (!coreDictItems.empty()) {
    for (auto iter = coreDictItems.begin(); 
        iter != coreDictItems.end();
        ++iter) {
      const CoreDictItem &coreDictItem = **iter;
      TriggeredNodes *triggeredNodes = new TriggeredNodes(offset, coreDictItem.GetName().length());
      results.push_back(triggeredNodes);
      basic::AnalysisTracer::Get()->Add(
          "triggerPrefixStr", 
          query.substr(
            triggeredNodes->GetEndOffset() - triggeredNodes->GetLen(), 
            triggeredNodes->GetLen()));
    }
  }
}

}}}
