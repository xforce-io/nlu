#include "../matcher.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace syntax {

const std::wstring Matcher::kSyntacticStoragePrefix = L"/syntactic";

Matcher::Matcher() :
    milkie_(new milkie::Milkie()) {}

bool Matcher::Init() {
  bool ret = milkie_->Init(Conf::Get().GetMilkieConfpath());
  if (!ret) {
    FATAL("fail_init[parser]");
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

void Matcher::Match(std::shared_ptr<basic::NluContext> nluContext) {
  while (Process_(nluContext)) {
  }
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

bool Matcher::Process_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  if (SyntaxProcessForChunkSep_(nluContext)) {
    touched = true;
  }

  if (SyntaxProcessForChunk_(nluContext)) {
    touched = true;
  }

  if (PostProcess_(nluContext)) {
    touched = true;
  }
  return touched;
}

bool Matcher::SyntaxProcessForChunkSep_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  auto cur = nluContext->GetChunkSeps().Begin();
  while (cur != nluContext->GetChunkSeps().End()) {
    auto next = cur;
    ++next;

    std::shared_ptr<basic::NluContext> fragment;
    if (next != nluContext->GetChunkSeps().End()) {
      fragment = nluContext->Build(
              (*cur)->GetOffset(),
              (*next)->GetOffset());
    } else {
      fragment = nluContext->Build(
              (*cur)->GetOffset(),
              nluContext->GetQuery().length());
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

    const milkie::Storage &storage = context->GetStorage();
    for (auto &storageKv : storage.Get()) {
      const milkie::StorageKey &key = storageKv.first;
      std::wstring repr;
      key.GetRepr(repr);

      std::vector<std::wstring> vals;
      StrHelper::SplitStr(repr, L'.', vals);
      if (vals.size() != 2) {
        continue;
      }

      auto storageItems = storageKv.second->Get();
      if (vals[0] == kSyntacticStoragePrefix) {
        if (vals.size() != 2) {
          ERROR("invalid_storage_key[" << repr << "]");
          continue;
        }

        auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
        if (basic::SyntaxTag::Type::kUndef == syntaxTag) {
          ERROR("unknown_syntax_tag[" << syntaxTag << "]");
          continue;
        }

        auto storageItems = storageKv.second->Get();
        for (auto &storageItem : storageItems) {
          basic::Chunk chunk(
                  syntaxTag,
                  storageItem.GetOffset() + (*cur)->GetOffset(),
                  storageItem.GetContent().length());
          if (nluContext->GetChunks().Add(chunk)) {
            touched = true;
          }
        }
      } else {
        FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
      }
    }
    cur = next;
  }
  return touched;
}

bool Matcher::SyntaxProcessForChunk_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  auto context = std::make_shared<milkie::Context>(nluContext);
  auto errCode = feChunk_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return false;
  }

  const milkie::Storage &storage = context->GetStorage();
  for (auto &storageKv : storage.Get()) {
    const milkie::StorageKey &key = storageKv.first;
    std::wstring repr;
    key.GetRepr(repr);

    std::vector<std::wstring> vals;
    StrHelper::SplitStr(repr, L'.', vals);
    if (vals.size() != 2) {
      continue;
    }

    auto storageItems = storageKv.second->Get();
    if (vals[0] == kSyntacticStoragePrefix) {
      auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
      if (basic::SyntaxTag::Type::kUndef == syntaxTag) {
        ERROR("unknown_syntax_tag[" << syntaxTag << "]");
        return false;
      }

      auto storageItems = storageKv.second->Get();
      for (auto &storageItem : storageItems) {
        basic::Chunk chunk(
                syntaxTag,
                storageItem.GetOffset(),
                storageItem.GetContent().length());
        if (nluContext->GetChunks().Add(chunk)) {
          if (basic::SyntaxTag::Type::kStc == syntaxTag) {
            return true;
          }
          touched = true;
        }
      }
    } else {
      FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
    }
  }
  return touched;
}

bool Matcher::PostProcess_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetTag() == basic::SyntaxTag::Type::kContNp) {
      auto segBefore = nluContext->GetSegments().GetFragmentBefore(chunk->GetOffset());
      auto segAfter = nluContext->GetSegments().GetFragmentAfter(chunk->GetOffset() + chunk->GetLen());
      bool beforeCond = (nullptr == segBefore ||
          (basic::PosTag::Type::kV != segBefore->GetTag() &&
              basic::PosTag::Type::kP != segBefore->GetTag()));

      bool afterCond = (nullptr == segAfter ||
          (!basic::PosTag::IsPredicate(segAfter->GetTag()) &&
          basic::PosTag::Type::kP != segBefore->GetTag()));

      if (beforeCond || afterCond) {
        basic::Chunk newChunk(
                basic::SyntaxTag::Type::kNp,
                chunk->GetOffset(),
                chunk->GetLen());
        if (nluContext->GetChunks().Add(newChunk)) {
          touched = true;
        }
      }
    }
  }
  return touched;
}

}}}
