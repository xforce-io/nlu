#include "../manager_triggers.h"
#include "../level_triggers.hpp"
#include "../trigger_refer.hpp"
#include "../trigger_prefix.hpp"
#include "../trigger_default.hpp"
#include "../trigger_compound.h"
#include "../../../numeric_recognizer.hpp"

namespace xforce { namespace nlu { namespace segmentor {

ManagerTriggers* ManagerTriggers::managerTriggers_ = new ManagerTriggers();

ManagerTriggers::ManagerTriggers() {
  LevelTriggers *levelTriggers0 = new LevelTriggers();
  levelTriggers0->AddTrigger(*(new TriggerRefer()));

  LevelTriggers *levelTriggers1 = new LevelTriggers();
  levelTriggers1->AddTrigger(*(new TriggerCompound()));

  LevelTriggers *levelTriggers2 = new LevelTriggers();
  levelTriggers2->AddTrigger(*(new TriggerPrefix()));

  LevelTriggers *levelTriggers3 = new LevelTriggers();
  levelTriggers3->AddTrigger(*(new TriggerDefault()));

  levelTriggers_.push_back(levelTriggers0);
  levelTriggers_.push_back(levelTriggers1);
  levelTriggers_.push_back(levelTriggers2);
  levelTriggers_.push_back(levelTriggers3);
}

void ManagerTriggers::Process(      
    Graph &graph, 
    const std::wstring &query, 
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
      XFC_DELETE(tmpContinousNodes)
      return;
    }
  }
  XFC_DELETE(tmpContinousNodes)
}

ManagerTriggers::~ManagerTriggers() {
  for (auto iter = levelTriggers_.begin(); iter != levelTriggers_.end(); ++iter) {
    XFC_DELETE(*iter)
  }
}

void ManagerTriggers::Tini() {
  XFC_DELETE(managerTriggers_)
}

}}}
