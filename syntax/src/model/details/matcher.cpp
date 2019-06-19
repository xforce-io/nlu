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

  feChunkSep_ = milkie_->GetManager().GetFeatureExtractor(L"syntaxFromChunk");
  if (feChunkSep_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_syntax_from_chunk");
    return false;
  }

  feChunk_ = milkie_->GetManager().GetFeatureExtractor(L"syntax");
  if (feChunk_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_syntax");
    return false;
  }
  return true;
}

void Matcher::Match(basic::NluContext &nluContext) {
  SyntaxProcessForChunkSep_(nluContext);
  SyntaxProcessForChunk_(nluContext);
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

bool Matcher::SyntaxProcessForChunkSep_(basic::NluContext &nluContext) {
  bool newChunkAdded = false;
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
    auto errCode = feChunkSep_->MatchPattern(*context);
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
          newChunkAdded = true;
        }
      } else {
        FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
      }
    }
    cur = next;
  }
  return newChunkAdded;
}

bool Matcher::SyntaxProcessForChunk_(basic::NluContext &nluContext) {
  bool newChunkAdded = false;
  auto context = std::make_shared<milkie::Context>(nluContext);
  auto errCode = feChunk_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return false;
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
        return false;
      }

      auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
      if (basic::SyntaxTag::kUndef == syntaxTag) {
        ERROR("unknown_syntax_tag[" << syntaxTag << "]");
        return false;
      }

      auto storageItems = storage.second->Get();
      for (auto &storageItem : storageItems) {
        basic::Chunk chunk(
                syntaxTag,
                storageItem.GetOffset(),
                storageItem.GetContent().length());
        nluContext.GetChunks().Add(chunk);
        newChunkAdded = true;
      }
    } else {
      FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
    }
  }
  return newChunkAdded;
}

}}}
