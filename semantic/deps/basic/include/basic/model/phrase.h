#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext;
class CollectionSyntaxTag;

class Phrase {
 public:
  Phrase(
          size_t from,
          size_t len,
          const NluContext &nluContext,
          std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag,
          uint32_t strategy);

  inline void SetNluContext(const NluContext &nluContext);

  size_t GetFrom() const { return from_; }
  size_t GetLen() const { return len_; }
  size_t GetEnd() const { return from_+len_; }
  const NluContext& GetNluContext() const { return *nluContext_; }
  const std::shared_ptr<CollectionSyntaxTag> GetCollectionSyntaxTag() const { return collectionSyntaxTag_; }
  std::shared_ptr<CollectionSyntaxTag> GetCollectionSyntaxTag() { return collectionSyntaxTag_; }
  uint32_t GetStrategy() const { return strategy_; }
  void GetSubQuery(std::wstring &subQuery) const;

 private:
  size_t from_;
  size_t len_;
  const NluContext *nluContext_;
  std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag_;
  uint32_t strategy_;
};

void Phrase::SetNluContext(const NluContext &nluContext) {
  nluContext_ = &nluContext;
}

}}}