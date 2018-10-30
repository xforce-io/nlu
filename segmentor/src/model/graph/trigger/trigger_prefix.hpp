#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Graph;
class TriggeredNodes;

class TriggerPrefix : public Trigger {
 public: 
  inline void Process(      
      IN const Graph &graph, 
      IN const std::string &query, 
      IN int offset, 
      OUT std::list<TriggeredNodes*> &results);
};

}}

#include "../../../data/manager.h"
#include "../../core_dict_item.h"
#include "../../../data/word_dict.h"
#include "../triggered_nodes.h"

namespace xforce { namespace nlu {

void TriggerPrefix::Process(      
    const Graph &graph, 
    const std::string &query, 
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
      results.push_back(new TriggeredNodes(offset, coreDictItem.GetName().length()));
    }
  }
}

}}
