#include "../BigramDict.h"

bool BigramDict::Init(const std::string &dictpath) {
  return true;
}

uint32_t BigramDict::getFreq(const std::string &word0, const std::string &word1) {
  auto iter = container_.find(word0);
  if (iter == container_.end()) {
    return 0;
  }

  auto iter1 = iter->second->find(word1);
  if (iter1 == iter->second) {
    return 0;
  }
  return iter1->second;
}

void BigramDict::addToDict(const std::string &word0, const std::string &word1, uint32_t freq) {
  auto iter = container_.find(word0);
  if (iter == container_.end()) {
    Inner *inner = new Inner;
    inner->insert(std::make_pair(word1, freq));
    container_.insert(std::make_pair(word0, inner));
    return;
  }

  auto iter1 = iter->second->find(word1);
  if (iter1 == iter->second->end()) {
    iter->second->insert(std::make_pair(word1, freq));
    return;
  }

  iter->second->insert(std::make_pair(word1, iter1->second + freq));
}

BigramDict::~BigramDict() {
  for (auto iter = container_.begin(); iter != container_.end(); ++iter) {
    XFC_DELETE(iter->second)
  }
}
