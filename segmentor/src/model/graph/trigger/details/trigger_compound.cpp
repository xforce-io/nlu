#include "../trigger_compound.h"
#include "../../graph.h"

namespace xforce { namespace nlu { namespace segmentor {

void TriggerCompound::Process(      
    Graph &graph, 
    const std::wstring &query, 
    int offset, 
    std::list<TriggeredNodes*> &results) {
  if (kMarkPunction != query[offset]) {
    return;
  }

  auto triggeredNodes = new TriggeredNodes(offset, 1);
  auto namesNodes = new TriggeredNodes();

  int lastOffset = offset;
  int offsetNextComma = query.find(kMarkPunction, offset+1);
  while (offsetNextComma > 0) {
    namesNodes->AddNode(
        triggeredNodes->AddNode(
          lastOffset+1, 
          offsetNextComma-lastOffset-1));
    triggeredNodes->AddNode(offsetNextComma, 1);

    lastOffset = offsetNextComma;
    offsetNextComma = query.find(kMarkPunction, lastOffset+1);
  }

  int nextOffset = -1;
  for (ssize_t i = lastOffset+1; i < (ssize_t)query.length(); ++i) {
    if (L'和' == query[i] || L'及' == query[i]) {
      namesNodes->AddNode(
          triggeredNodes->AddNode(
            lastOffset+1, 
            i-lastOffset-1));
      triggeredNodes->AddNode(i, 1, basic::PosTag::Type::kC);
      nextOffset = i+1;
      break;
    } else if (L'以' == query[i] || L'及' == query[i+1]) {
      namesNodes->AddNode(
          triggeredNodes->AddNode(
            lastOffset+1,
            i-lastOffset-1));
      triggeredNodes->AddNode(i, 2, basic::PosTag::Type::kC);
      nextOffset = i+2;
      break;
    }
  }

  bool isName = true;
  if (namesNodes->GetNodes().size() != 0) {
    for (auto iter = namesNodes->GetNodes().begin(); iter != namesNodes->GetNodes().end(); ++iter) {
      Node *node = *iter;
      if (ner::PersonName::PossibleName(query, node->GetOffset(), node->GetLen()) < 0) {
        isName = false;
      }
    }
  } else {
    isName = false;
  }

  if (isName) {
    for (auto iter = namesNodes->GetNodes().begin(); iter != namesNodes->GetNodes().end(); ++iter) {
      Node &node = **iter;
      node.SetNameEntity(std::shared_ptr<basic::NameEntity>(new ner::PersonName(
              query.substr(node.GetOffset(), node.GetLen()),
              node.GetOffset())));
      graph.AddMaxPrioredNegLogPossi(node);
    }

    //find prev
    int prevNameOffset = ner::PersonName::FindNameFromEnd(query.substr(0, offset));
    if (prevNameOffset >= 0) {
      graph.AddMaxPrioredNegLogPossi(
          *AddNewPersonName_(query, *triggeredNodes, prevNameOffset, offset - prevNameOffset));
    }

    //find next
    if (nextOffset > 0) {
      if (ner::PersonName::PossibleName(query, nextOffset, 2) >= 0) {
        AddNewPersonName_(query, *triggeredNodes, nextOffset, 2);
      }

      if (ner::PersonName::PossibleName(query, nextOffset, 3) >= 0) {
        auto otherTriggeredNodes = new TriggeredNodes();
        AddNewPersonName_(query, *otherTriggeredNodes, nextOffset, 3);
        results.push_back(otherTriggeredNodes);
      }
    }
    results.push_back(triggeredNodes);
  }
}

}}}
