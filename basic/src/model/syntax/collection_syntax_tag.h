#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace basic {

class CollectionSyntaxTag {
 public:
  explicit CollectionSyntaxTag(bool isStc);
  explicit CollectionSyntaxTag(basic::SyntaxTag::Type::Val tag);
  explicit CollectionSyntaxTag(const CollectionSyntaxTag &endTags);

  void Add(basic::SyntaxTag::Type::Val tag);
  void Clear();

  std::list<basic::SyntaxTag::Type::Val> GetTags() const { return tags_; }
  inline bool IsStc() const;
  inline bool ContainTag(basic::SyntaxTag::Type::Val tag) const;

  static std::wstring Str(const CollectionSyntaxTag &endTags);

 private:
  std::list<basic::SyntaxTag::Type::Val> tags_;
};

bool CollectionSyntaxTag::IsStc() const {
  return tags_.size() == 1 && \
      tags_.front() == basic::SyntaxTag::Type::kStc;
}

bool CollectionSyntaxTag::ContainTag(basic::SyntaxTag::Type::Val tag) const {
  for (auto &singleTag : tags_) {
    if (singleTag == tag) {
      return true;
    }
  }
  return false;
}

}}}