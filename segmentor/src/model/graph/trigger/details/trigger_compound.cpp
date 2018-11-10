#include "../trigger_compound.h"
#include "../../triggered_nodes.h"
#include "../../../ner/person_name.h"
#include "../../graph.h"

namespace xforce { namespace nlu {

void TriggerCompound::Process(      
    IN Graph &graph, 
    IN const std::wstring &query, 
    IN int offset, 
    OUT std::list<TriggeredNodes*> &results) {
  if (kMarkPunction != query[offset]) {
    return;
  }

  auto newTriggeredNodes = new TriggeredNodes(offset, 1);
  auto namesNodes = new TriggeredNodes();

  int lastOffset = offset;
  int offsetNextComma = query.find(kMarkPunction, offset+1);
  while (offsetNextComma > 0) {
    namesNodes->AddNode(
        newTriggeredNodes->AddNode(
          lastOffset+1, 
          offsetNextComma-lastOffset-1));
    newTriggeredNodes->AddNode(offsetNextComma, 1);

    lastOffset = offsetNextComma;
    offsetNextComma = query.find(kMarkPunction, lastOffset+1);
  }

  for (ssize_t i = lastOffset+1; i < (ssize_t)query.length(); ++i) {
    if (L'和' == query[i] || L'及' == query[i]) {
      namesNodes->AddNode(
          newTriggeredNodes->AddNode(
            lastOffset+1, 
            i-lastOffset-1));
      newTriggeredNodes->AddNode(i, 1);
      offsetNextComma = i;
      break;
    } else if (L'以' == query[i] || L'及' == query[i+1]) {
      namesNodes->AddNode(
          newTriggeredNodes->AddNode(
            lastOffset+1,
            i-lastOffset-1));
      newTriggeredNodes->AddNode(i, 2);
      offsetNextComma = i+1;
      break;
    }
  }

  bool isName = true;
  for (auto iter = namesNodes->GetNodes().begin(); iter != namesNodes->GetNodes().end(); ++iter) {
    Node *node = *iter;
    if (PersonName::PossibleName(query, node->GetOffset(), node->GetLen()) < 0) {
      isName = false;
    }
  }

  if (isName) {
    for (auto iter = namesNodes->GetNodes().begin(); iter != namesNodes->GetNodes().end(); ++iter) {
      Node &node = **iter;
      node.SetNer(*(new PersonName(query.substr(node.GetOffset(), node.GetLen()))));
      graph.AddMaxPrioredNegLogPossi(node);
    }

    int prevNameOffset = PersonName::FindNameFromEnd(query.substr(0, offset));
    if (prevNameOffset >= 0) {
      auto newNode = new Node(prevNameOffset, offset-prevNameOffset);
      newNode->SetNer(*(new PersonName(query.substr(prevNameOffset, offset - prevNameOffset))));
      newTriggeredNodes->AddNode(*newNode);
      graph.AddMaxPrioredNegLogPossi(*newNode);
    }
    results.push_back(newTriggeredNodes);
  }
}

}}
