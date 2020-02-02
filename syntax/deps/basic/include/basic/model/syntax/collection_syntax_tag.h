#pragma once

#include "../../public.h"
#include "syntax_tag.h"

namespace xforce { namespace nlu { namespace basic {

class CollectionSyntaxTag {
 public:
  explicit CollectionSyntaxTag(bool isStc);
  explicit CollectionSyntaxTag(SyntaxTag::Type::Val tag);
  explicit CollectionSyntaxTag(const CollectionSyntaxTag &endTags);

  void Add(SyntaxTag::Type::Val tag);
  void Clear();

  std::list<SyntaxTag::Type::Val> GetTags() const { return tags_; }
  inline bool IsStc() const;
  inline bool ContainTag(SyntaxTag::Type::Val tag) const;

  static std::wstring Str(const CollectionSyntaxTag &endTags);

 private:
  std::list<SyntaxTag::Type::Val> tags_;
};

bool CollectionSyntaxTag::IsStc() const {
  return tags_.size() == 1 && \
      tags_.front() == SyntaxTag::Type::kStc;
}

bool CollectionSyntaxTag::ContainTag(SyntaxTag::Type::Val tag) const {
  for (auto &singleTag : tags_) {
    if (singleTag == tag) {
      return true;
    }
  }
  return false;
}

}}}
