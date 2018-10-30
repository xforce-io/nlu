#include "../manager_triggers.h"
#include "../level_triggers.hpp"
#include "../trigger_refer.hpp"
#include "../trigger_prefix.hpp"
#include "../trigger_default.hpp"
#include "../../../numeric_recognizer.hpp"

namespace xforce { namespace nlu {

ManagerTriggers* ManagerTriggers::managerTriggers_ = new ManagerTriggers();

ManagerTriggers::ManagerTriggers() {
  LevelTriggers *levelTriggers0 = new LevelTriggers();
  levelTriggers0->AddTrigger(*(new TriggerRefer()));

  LevelTriggers *levelTriggers1 = new LevelTriggers();
  //TODO:add a trigger
  levelTriggers1->AddTrigger(*(new TriggerPrefix()));

  LevelTriggers *levelTriggers2 = new LevelTriggers();
  levelTriggers2->AddTrigger(*(new TriggerDefault()));

  levelTriggers_.push_back(levelTriggers0);
  levelTriggers_.push_back(levelTriggers1);
  levelTriggers_.push_back(levelTriggers2);
}

void ManagerTriggers::Process(      
    const Graph &graph, 
    const std::string &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
  int minLen = NumericRecognizer::ExtractArabicNumeral(query, offset);
  if (minLen>0) {
    results.push_back(new TriggeredNodes(offset, minLen));
  }

  auto tmpContinousNodes = new std::list<TriggeredNodes*>();
  for (auto iter = levelTriggers_.begin(); iter != levelTriggers_.end(); ++iter) {
    (*iter)->Process(graph, query, offset, *tmpContinousNodes);
    if (!tmpContinousNodes->empty()) {
      if (minLen>0) {
        for (auto iter1 = tmpContinousNodes->begin(); 
            iter1 != tmpContinousNodes->end(); 
            ++iter1) {
          if ((*iter1)->GetLen() >= (size_t)minLen) {
            results.push_back(*iter1);
          }
        }
      } else {
        for (auto iter1 = tmpContinousNodes->begin(); 
            iter1 != tmpContinousNodes->end(); 
            ++iter1) {
          results.push_back(*iter1);
        }
      }
      return;
    }
  }
}

ManagerTriggers::~ManagerTriggers() {
  for (auto iter = levelTriggers_.begin(); iter != levelTriggers_.end(); ++iter) {
    XFC_DELETE(*iter)
  }
}

}}
