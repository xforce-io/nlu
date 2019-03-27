#include "../matcher.h"

namespace xforce { namespace nlu { namespace chunker {

const std::wstring Matcher::kChunkStoragePrefix = L"chunk.";

Matcher::Matcher() :
    milkie_(new milkie::Milkie()) {}

bool Matcher::Init() {
  bool ret = milkie_->Init("conf/milkie.conf");
  if (!ret) {
    FATAL("fail_init[milkie]");
    return false;
  }

  featureExtractor_ = milkie_->GetManager().GetFeatureExtractor(L"chunker");
  if (featureExtractor_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_chunker");
    return false;
  }
  return true;
}

void Matcher::Match(basic::NluContext &nluContext) {
  auto context = std::make_shared<milkie::Context>(nluContext.GetQuery());
  auto errCode = featureExtractor_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return;
  }

  std::unordered_map<std::wstring, std::shared_ptr<milkie::StorageVal>> storages;
  context->GetStorages(storages);
  for (auto storage : storages) {
    if (storage.first.length() <= kChunkStoragePrefix.length()) {
      continue;
    }

    auto prefix = storage.first.substr(0, kChunkStoragePrefix.length());
    if (kChunkStoragePrefix != prefix) {
      continue;
    }

    auto postfix = storage.first.substr(kChunkStoragePrefix.length());
    auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(postfix);
    if (basic::SyntaxTag::kUndef == syntaxTag) {
      ERROR("unknown_syntax_tag[" << syntaxTag << "]");
      continue;
    }

    auto storageItems = storage.second->Get();
    for (auto storageItem : storageItems) {
      basic::Chunk chunk(syntaxTag, storageItem.);
      nluContext.GetChunks().Add()
    }
  }
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

}}}
