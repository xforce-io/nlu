#include "../matcher.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace syntax {

const std::wstring Matcher::kSyntacticStoragePrefix = L"/syntactic";

Matcher::Matcher() :
    milkie_(new milkie::Milkie()) {}

bool Matcher::Init() {
  bool ret = milkie_->Init(Conf::Get().GetMilkieConfpath());
  if (!ret) {
    FATAL("fail_init[milkie]");
    return false;
  }

  featureExtractor_ = milkie_->GetManager().GetFeatureExtractor(L"syntax");
  if (featureExtractor_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_syntax");
    return false;
  }
  return true;
}

void Matcher::Match(basic::NluContext &nluContext) {
  auto cur = nluContext.GetChunkSeps().Begin();
  while (cur != nluContext.GetChunkSeps().End()) {
    auto next = cur;
    ++next;

    std::shared_ptr<basic::NluContext> fragment;
    if (next != nluContext.GetChunkSeps().End()) {
      fragment = nluContext.Build(
              (*cur)->GetOffset(),
              (*next)->GetOffset());
    } else {
      fragment = nluContext.Build(
              (*cur)->GetOffset(),
              nluContext.GetQuery().length());
    }

    if (fragment == nullptr) {
      cur = next;
      continue;
    }

    auto context = std::make_shared<milkie::Context>(fragment);
    auto errCode = featureExtractor_->MatchPattern(*context);
    if (milkie::Errno::kOk != errCode) {
      cur = next;
      continue;
    }

    std::unordered_map<std::wstring, std::shared_ptr<milkie::StorageVal>> storages;
    context->GetStorages(storages);
    for (auto &storage : storages) {
      const std::wstring &key = storage.first;
      std::vector<std::wstring> vals;
      StrHelper::SplitStr(key, L'.', vals);
      if (vals.size() != 2) {
        continue;
      }

      auto storageItems = storage.second->Get();
      if (vals[0] == kSyntacticStoragePrefix) {
        if (vals.size() != 2) {
          ERROR("invalid_storage_key[" << key << "]");
          continue;
        }

        auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
        if (basic::SyntaxTag::kUndef == syntaxTag) {
          ERROR("unknown_syntax_tag[" << syntaxTag << "]");
          continue;
        }

        auto storageItems = storage.second->Get();
        for (auto &storageItem : storageItems) {
          basic::Chunk chunk(
                  syntaxTag,
                  storageItem.GetOffset() + (*cur)->GetOffset(),
                  storageItem.GetContent().length());
          nluContext.GetChunks().Add(chunk);
        }
      } else {
        FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
      }
    }
    cur = next;
  }
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

}}}
