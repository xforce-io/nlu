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
          std::shared_ptr<NluContext> nluContext,
          std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag,
          uint32_t strategy);

  size_t GetFrom() const { return from_; }
  size_t GetLen() const { return len_; }
  size_t GetEnd() const { return from_+len_; }
  const std::shared_ptr<NluContext>& GetNluContext() const { return nluContext_; }
  std::shared_ptr<NluContext>& GetNluContext() { return nluContext_; }
  const std::shared_ptr<CollectionSyntaxTag> GetCollectionSyntaxTag() const { return collectionSyntaxTag_; }
  std::shared_ptr<CollectionSyntaxTag> GetCollectionSyntaxTag() { return collectionSyntaxTag_; }
  uint32_t GetStrategy() const { return strategy_; }
  void GetSubQuery(std::wstring &subQuery) const;

 private:
  size_t from_;
  size_t len_;
  std::shared_ptr<NluContext> nluContext_;
  std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag_;
  uint32_t strategy_;
};

}}}
