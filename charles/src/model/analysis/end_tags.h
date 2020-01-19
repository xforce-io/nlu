#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class EndTags {
 public:
  explicit EndTags(bool isStc=true);
  explicit EndTags(basic::SyntaxTag::Type::Val tag);
  explicit EndTags(const EndTags &endTags);

  void Add(basic::SyntaxTag::Type::Val tag);
  void Clear();

  std::list<basic::SyntaxTag::Type::Val> GetTags() const { return tags_; }
  inline bool IsStc() const;
  inline bool ContainTag(basic::SyntaxTag::Type::Val tag) const;

  static std::wstring Str(const EndTags &endTags);

 private:
  std::list<basic::SyntaxTag::Type::Val> tags_;
};

bool EndTags::IsStc() const {
  return tags_.size() == 1 && \
      tags_.front() == basic::SyntaxTag::Type::kStc;
}

bool EndTags::ContainTag(basic::SyntaxTag::Type::Val tag) const {
  for (auto &singleTag : tags_) {
    if (singleTag == tag) {
      return true;
    }
  }
  return false;
}

}}}