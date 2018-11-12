#include "../triggered_nodes.h"

namespace xforce { namespace nlu { namespace segmentor {

TriggeredNodes::TriggeredNodes(Node *singleNode) {
  if (NULL != singleNode) {
    nodes_.push_back(singleNode);
    len_ = singleNode->GetLen();
    endOffset_ = singleNode->GetOffset() + singleNode->GetLen();
  } else {
    len_ = 0;
    endOffset_ = -1;
  }
}

TriggeredNodes::TriggeredNodes() :
  TriggeredNodes(NULL) {}

TriggeredNodes::TriggeredNodes(int offset, size_t length) :
  TriggeredNodes(new Node(offset, length)) {}

std::string TriggeredNodes::Str() const {
  std::stringstream ss;
  ss << "( ";
  for (auto iter = nodes_.begin(); iter != nodes_.end(); ++iter) {
    ss << (*iter)->Str();
  }
  ss << "/" << len_ << "/" << endOffset_ << ")";
  return ss.str();
}

}}}
