#include "../collection_syntax_tag.h"

namespace xforce { namespace nlu { namespace basic {

CollectionSyntaxTag::CollectionSyntaxTag(bool isStc) {
  if (isStc) {
    tags_.push_back(SyntaxTag::Type::kStc);
  }
}

CollectionSyntaxTag::CollectionSyntaxTag(SyntaxTag::Type::Val tag) {
  tags_.push_back(tag);
}

CollectionSyntaxTag::CollectionSyntaxTag(const CollectionSyntaxTag &endTags) {
  for (auto &tag : endTags.GetTags()) {
    tags_.push_back(tag);
  }
}

void CollectionSyntaxTag::Add(SyntaxTag::Type::Val tag) {
  tags_.push_back(tag);
}

void CollectionSyntaxTag::Clear() {
  tags_.clear();
}

std::wstring CollectionSyntaxTag::Str(const CollectionSyntaxTag &endTags) {
  std::wstringstream wss;
  for (auto &tag : endTags.GetTags()) {
    wss << SyntaxTag::Str(tag) << L",";
  }
  return wss.str();
}

}}}
