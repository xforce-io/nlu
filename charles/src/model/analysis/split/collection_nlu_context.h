#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class CollectionNluContext {
 public:
  typedef std::vector<std::shared_ptr<basic::NluContext>> Container;

 public:
  inline bool Add(std::shared_ptr<basic::NluContext> newNluContext);
  inline void Clear();

  Container& Get() { return container_; }
  inline bool Empty() const;
  inline bool NonEmpty() const;

 private:
  Container container_;
};

bool CollectionNluContext::Add(std::shared_ptr<basic::NluContext> newNluContext) {
  if (newNluContext->GetIsValid(true)) {
    container_.push_back(newNluContext);
    return true;
  }
  return false;
}

void CollectionNluContext::Clear() {
  container_.clear();
}

bool CollectionNluContext::Empty() const {
  return container_.empty();
}

bool CollectionNluContext::NonEmpty() const {
  return !container_.empty();
}

}}}
