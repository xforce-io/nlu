#include "../end_tags.h"

namespace xforce { namespace nlu { namespace charles {

EndTags::EndTags(bool isStc) {
  if (isStc) {
    tags_.push_back(basic::SyntaxTag::Type::kStc);
  }
}

EndTags::EndTags(basic::SyntaxTag::Type::Val tag) {
  tags_.push_back(tag);
}

EndTags::EndTags(const EndTags &endTags) {
  for (auto &tag : endTags.GetTags()) {
    tags_.push_back(tag);
  }
}

void EndTags::Add(basic::SyntaxTag::Type::Val tag) {
  tags_.push_back(tag);
}

void EndTags::Clear() {
  tags_.clear();
}

std::wstring EndTags::Str(const EndTags &endTags) {
  std::wstringstream wss;
  for (auto &tag : endTags.GetTags()) {
    wss << basic::SyntaxTag::Str(tag) << L",";
  }
  return wss.str();
}

}}}